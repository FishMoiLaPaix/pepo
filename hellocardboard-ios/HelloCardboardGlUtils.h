/*
<<<<<<< HEAD
 * Copyright 2019 Google LLC
=======
 * Copyright 2019 Google LLC. All Rights Reserved.
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef HELLO_CARDBOARD_IOS_HELLO_CARDBOARD_UTILS_H_
#define HELLO_CARDBOARD_IOS_HELLO_CARDBOARD_UTILS_H_

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <errno.h>

#include <cstdint>
#include <cstdlib>
#include <functional>
#include <string>
#include <vector>

namespace cardboard {
namespace hello_cardboard {
<<<<<<< HEAD

=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
/**
 * Generates a random floating point number between |min| and |max|.
 */
float RandomUniformFloat(float min, float max);

/**
 * Generates a random integer in the range [0, max_val).
 */
int RandomUniformInt(int max_val);

/**
 * Computes the angle between two vectors; see
 * https://en.wikipedia.org/wiki/Vector_projection#Definitions_in_terms_of_a_and_b.
 */
float AngleBetweenVectors(const std::array<float, 3>& vec1,
                          const std::array<float, 3>& vec2);

/**
 * Converts a string into an OpenGL ES shader.
 *
 * @param type The type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
 * @param shader_source The source code of the shader.
 * @return The shader object handler, or 0 if there's an error.
 */
GLuint LoadGLShader(GLenum type, const char* shader_source);

/**
 * Checks for OpenGL errors.
 */
void CheckGLError(const char* label);

/**
 * Mesh generated from an .obj that can be rendered with OpenGL.
 */
class TexturedMesh {
 public:
  TexturedMesh();

  /**
   * Initializes the mesh from a .obj file.
   *
   * @return True if initialization was successful.
   */
<<<<<<< HEAD
  bool Initialize(const std::string& obj_file_path, GLuint position_attrib,
                  GLuint uv_attrib);
=======
  bool Initialize(std::string objFilePath, GLuint positionAttrib,
                  GLuint uvAttrib);
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

  /**
   * Draws the mesh. The u_MVP uniform should be set before calling this using
   * glUniformMatrix4fv(), and a texture should be bound to GL_TEXTURE0.
   */
  void Draw() const;

 private:
<<<<<<< HEAD
  std::vector<GLfloat> vertices_;
  std::vector<GLfloat> uv_;
  std::vector<GLushort> indices_;
  GLuint position_attrib_;
  GLuint uv_attrib_;
=======
  std::vector<GLfloat> _vertices;
  std::vector<GLfloat> _uv;
  std::vector<GLushort> _indices;
  GLuint _positionAttrib;
  GLuint _uvAttrib;
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
};

/**
 * Texture generated from a .png that can be used with OpenGL.
 */
class Texture {
 public:
  Texture();

  ~Texture();

  /**
   * Initializes the texture.
   *
   * After this is called the texture will be bound, replacing any previously
   * bound texture.
   *
   * @return True if initialization was successful.
   */
<<<<<<< HEAD
  bool Initialize(const std::string& image_name);
=======
  bool Initialize(std::string imageName);
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

  /**
   * Binds the texture, replacing any previously bound texture.
   */
  void Bind() const;

 private:
<<<<<<< HEAD
  GLuint texture_id_;
=======
  GLuint _textureId;
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
};

}  // namespace hello_cardboard
}  // namespace cardboard

#endif  // HELLO_CARDBOARD_IOS_HELLO_CARDBOARD_UTILS_H_
