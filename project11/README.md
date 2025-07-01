# Project 11: Animated transformation

## Takeaways

* This example is similar to the previous one with the exception that it continuously updates the rotation transformation angle. Note that `glm` library operates with radians thus the angle should be converted prior to be used by the `glm::rotate` function.
```
static float rot = 0.0f;
rot = (rot + 1) % 360;
trans = glm::rotate(trans, glm::radians(rot), glm::vec3(0.0, 0.0, 1.0));
```
**NOte:** FreeGLUT call the dispkay callback function only when on system requests such as resize, minimize / maximize, etc. To force the redisplay an explicit call to the `glutPostRedisplay` is added to the callback function.