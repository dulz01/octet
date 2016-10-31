////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Sprite class for Invaderers
//

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

namespace octet {
  class sprite {
    // where is our sprite (overkill for a 2D game!)
    mat4t modelToWorld;

    // half the width of the sprite
    float halfWidth;

    // half the height of the sprite
    float halfHeight;

    // what texture is on our sprite
    int texture;

    // true if this sprite is enabled.
    bool enabled;

    // animation data for the sprite
    int frameNumber;

    // specifies the dimensions of the sprite sheet
    int numFramesInX;
    int numFramesInY;

    // size of the whole texture. Used for calculations.
    float textureWidth;
    float textureHeight;

    // the size of the frame within the sprite sheet
    float frameWidth;
    float frameHeight;

    // the frame coordinates
    float frameXLeft;
    float frameXRight;
    float frameYBottom;
    float frameYTop;
  public:
    sprite() {
      texture = 0;
      enabled = true;
    }

    void init(int _texture, float x, float y, float w, float h, int numFramesX, int numFramesY) {
      modelToWorld.loadIdentity();
      modelToWorld.translate(x, y, 0);
      halfWidth = w * 0.5f;
      halfHeight = h * 0.5f;
      texture = _texture;
      enabled = true;

      // animation data
      frameNumber = 0;
      numFramesInX = numFramesX;
      numFramesInY = numFramesY;
      textureWidth = w;
      textureHeight = h;

      // finding the size of the frame
      frameWidth = textureWidth / numFramesInX;
      frameHeight = textureHeight / numFramesInY;

      // finding the left hand side and the right hand side of the frame.
      frameXLeft = (frameNumber % numFramesInX) * frameWidth;
      frameXRight = frameXLeft + frameWidth;

      // finding the bottom of the frame.
      // (frameNumber / numFramesInX) finds the row the frame is on in the sprite sheet.
      // multiplying it by frameHeight finds the top of the frame.
      // subtracting the textureHeight by the value given finds the bottom of the frame.
      // subtracting the value further by frameHeight gives the value corresponding to the 
      // texture coordinates.
      frameYBottom = (textureHeight - ((frameNumber / numFramesInX) * frameHeight)) - frameHeight;

      // finding the top of the frame.
      frameYTop = frameYBottom + frameHeight;
    }

    void render(texture_shader &shader, mat4t &cameraToWorld) {
      // invisible sprite... used for gameplay.
      if (!texture) return;

      // build a projection matrix: model -> world -> camera -> projection
      // the projection space is the cube -1 <= x/w, y/w, z/w <= 1
      mat4t modelToProjection = mat4t::build_projection_matrix(modelToWorld, cameraToWorld);

      // set up opengl to draw textured triangles using sampler 0 (GL_TEXTURE0)
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture);

      // use "old skool" rendering
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      shader.render(modelToProjection, 0);

      // this is an array of the positions of the corners of the sprite in 3D
      // a straight "float" here means this array is being generated here at runtime.
      float vertices[] = {
        -halfWidth, -halfHeight, 0,
        halfWidth, -halfHeight, 0,
        halfWidth,  halfHeight, 0,
        -halfWidth,  halfHeight, 0,
      };

      // attribute_pos (=0) is position of each corner
      // each corner has 3 floats (x, y, z)
      // there is no gap between the 3 floats and hence the stride is 3*sizeof(float)
      glVertexAttribPointer(attribute_pos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)vertices);
      glEnableVertexAttribArray(attribute_pos);

      // normalize the frame data for tex coords
      frameXLeft = frameXLeft / textureWidth;
      frameXRight = frameXRight / textureWidth;
      frameYBottom = frameYBottom / textureHeight;
      frameYTop = frameYTop / textureHeight;

      // this is an array of the positions of the corners of the texture in 2D
      static const float uvs[] = {
        frameXLeft,  frameYBottom,
        frameXRight,  frameYBottom,
        frameXRight,  frameYTop,
        frameXLeft,  frameYTop,
      };

      // attribute_uv is position in the texture of each corner
      // each corner (vertex) has 2 floats (x, y)
      // there is no gap between the 2 floats and hence the stride is 2*sizeof(float)
      glVertexAttribPointer(attribute_uv, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)uvs);
      glEnableVertexAttribArray(attribute_uv);

      // finally, draw the sprite (4 vertices)
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    // move the object
    void translate(float x, float y) {
      modelToWorld.translate(x, y, 0);
    }

    // position the object relative to another.
    void set_relative(sprite &rhs, float x, float y) {
      modelToWorld = rhs.modelToWorld;
      modelToWorld.translate(x, y, 0);
    }

    // return true if this sprite collides with another.
    // note the "const"s which say we do not modify either sprite
    bool collides_with(const sprite &rhs) const {
      float dx = rhs.modelToWorld[3][0] - modelToWorld[3][0];
      float dy = rhs.modelToWorld[3][1] - modelToWorld[3][1];

      // both distances have to be under the sum of the halfwidths
      // for a collision
      return
        (fabsf(dx) < halfWidth + rhs.halfWidth) &&
        (fabsf(dy) < halfHeight + rhs.halfHeight)
        ;
    }

    bool is_above(const sprite &rhs, float margin) const {
      float dx = rhs.modelToWorld[3][0] - modelToWorld[3][0];

      return
        (fabsf(dx) < halfWidth + margin)
        ;
    }

    bool &is_enabled() {
      return enabled;
    }
  };
}
#endif