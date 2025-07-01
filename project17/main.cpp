#include <GL/glew.h>
#include <GL/freeglut.h>

#include "file_utils.h"
#include "transformation.h"
#include "camera.h"
#include "texture.h"

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 1024

struct Vertex
{
  glm::vec3 mPos;
  glm::vec2 mTex;

  Vertex() {}

  Vertex(glm::vec3 pos, glm::vec2 tex)
  {
    mPos = pos;
    mTex = tex;
  }
};

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;
GLuint gSampler;
Texture* pTexture = NULL;
Camera* gGameCamera = new Camera();
PerspectiveProjection gPersProj;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderSceneCB()
{
  glClear(GL_COLOR_BUFFER_BIT);

  static float Scale = 0.0f;

  Scale += 0.1f;

  Transformation trans;
  trans.Rotate(0.0f, Scale, 0.0f);
  trans.Translate(0.0f, 0.0f, 3.0f);
  trans.SetCamera(gGameCamera);
  trans.SetPerspectiveProj(gPersProj);

  glUniformMatrix4fv(gWVPLocation, 1, GL_FALSE, trans.GetWVPTrans());

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  pTexture->Bind(GL_TEXTURE0);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  glutSwapBuffers();
}

static void SpecialKeyboardCB(int Key, int x, int y)
{
  gGameCamera->OnKeyboard(Key);
}

static void KeyboardCB(unsigned char Key, int x, int y)
{
  switch (Key) {
    case 'q':
      glutLeaveMainLoop();
  }
}

static void PassiveMouseCB(int x, int y)
{
  gGameCamera->OnMouse(x, y);
}

static void MouseEntryCB(int state)
{
  if (state == GLUT_LEFT)
  {
    glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  }
  gGameCamera->Reset();
}

static void InitializeGlutCallbacks()
{
  glutDisplayFunc(RenderSceneCB);
  glutIdleFunc(RenderSceneCB);
  glutSpecialFunc(SpecialKeyboardCB);
  glutPassiveMotionFunc(PassiveMouseCB);
  glutEntryFunc(MouseEntryCB);
  glutKeyboardFunc(KeyboardCB);
}

static void CreateVertexBuffer()
{
  Vertex Vertices[4] = { Vertex(glm::vec3(-1.0f, -1.0f, 0.5773f), glm::vec2(0.0f, 0.0f)),
                         Vertex(glm::vec3(0.0f, -1.0f, -1.15475f), glm::vec2(0.5f, 0.0f)),
                         Vertex(glm::vec3(1.0f, -1.0f, 0.5773f), glm::vec2(1.0f, 0.0f)),
                         Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f)) };

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
  unsigned int Indices[] = { 1, 3, 0,
                             2, 3, 1,
                             0, 3, 2,
                             2, 1, 0 };

  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
  GLuint ShaderObj = glCreateShader(ShaderType);

  if (ShaderObj == 0) {
    fprintf(stderr, "Error creating shader type %d\n", ShaderType);
    exit(1);
  }

  const GLchar* p[1];
  p[0] = pShaderText;
  GLint Lengths[1];
  Lengths[0]= strlen(pShaderText);
  glShaderSource(ShaderObj, 1, p, Lengths);
  glCompileShader(ShaderObj);
  GLint success;
  glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
    exit(1);
  }

  glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders()
{
  GLuint ShaderProgram = glCreateProgram();

  if (ShaderProgram == 0) {
    fprintf(stderr, "Error creating shader program\n");
    exit(1);
  }

  std::string vs, fs;

  if (!ReadFile(pVSFileName, vs)) {
    exit(1);
  };

  if (!ReadFile(pFSFileName, fs)) {
    exit(1);
  };

  AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
  AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

  GLint Success = 0;
  GLchar ErrorLog[1024] = { 0 };

  glLinkProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
  if (Success == 0) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  glValidateProgram(ShaderProgram);
  glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
  if (!Success) {
    glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
    fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    exit(1);
  }

  glUseProgram(ShaderProgram);

  gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
  assert(gWVPLocation != 0xFFFFFFFF);
  gSampler = glGetUniformLocation(ShaderProgram, "gSampler");
  assert(gSampler != 0xFFFFFFFF);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Project 17: ");
  glutGameModeString("1280x1024@32");

  InitializeGlutCallbacks();

  // Must be done after glut is initialized!
  GLenum res = glewInit();
  if (res != GLEW_OK) {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return 1;
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  CreateVertexBuffer();
  CreateIndexBuffer();

  CompileShaders();

  glUniform1i(gSampler, 0);

  pTexture = new Texture(GL_TEXTURE_2D, "test.png");

  if (!pTexture->Load()) {
      return 1;
  }

  gPersProj.FOV = 60.0f;
  gPersProj.Height = WINDOW_HEIGHT;
  gPersProj.Width = WINDOW_WIDTH;
  gPersProj.zNear = 1.0f;
  gPersProj.zFar = 100.0f;                

  glutMainLoop();

  return 0;
}
