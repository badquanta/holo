#pragma once
#define HOLO_MAX_BONE_INFLUENCE 4
#include <holo/gl/Buffer.hh>
#include <holo/gl/SlProgram.hh>
#include <holo/gl/Texture.hh>
#include <holo/gl/VertexArray.hh>
namespace holo {
  /** Implemented with model-view example:
   * \todo Review, possibly refactor depending on what we need to support various models.
  */
  struct GlVertexInfluences {
      /** \todo should this be uint32_t? */
      int32_t m_BoneID;
      float   m_Weight;
  };
  // /** Structure of Vertices expected by `GlMesh` */
  struct GlVertex {
      vec3  Position;
      vec3  Normal;
      vec2  TexCoords;
      vec3  Tangent;
      vec3  Bitangent;
      int   m_BoneIDs[HOLO_MAX_BONE_INFLUENCE];
      float m_Weights[HOLO_MAX_BONE_INFLUENCE];
  };
  /** Type of buffer `GlMesh` uses..*/
  using GlVertexBuffer = GlBuffer<GL_ARRAY_BUFFER, GlVertex, GL_STATIC_DRAW>;
  /** Implemented from LearnOpenGL.com's example.
   * \todo Refactor to split SDL and OpenGL dependencies
  */
  class GlMesh {
    public:
      vector<GlVertex>              vertices;
      vector<uint32_t>              indices;
      vector<shared_ptr<GlTexture>> textures;
      shared_ptr<GlVertexArray>     VAO;

      GlMesh(
        vector<GlVertex> vertices, vector<uint32_t> indices, vector<shared_ptr<GlTexture>> textures
      );
      void Draw(shared_ptr<GlSlProgram> program);

    private:
      shared_ptr<GlVertexBuffer> VBO;
      shared_ptr<GlElementArrayBuffer> EBO;

      void SetupMesh();
  };
}