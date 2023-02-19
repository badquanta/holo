#pragma once
#define HOLO_MAX_BONE_INFLUENCE 4
#include <holo/gl/Buffer.hh>
#include <holo/gl/SlProgram.hh>
#include <holo/gl/Texture.hh>
#include <holo/gl/VertexArray.hh>
namespace holo {
  struct GlVertexInfluences {
      /** \todo should this be uint32_t? */
      int32_t m_BoneID;
      float   m_Weight;
  };
  struct GlVertex {
      vec3  Position;
      vec3  Normal;
      vec2  TexCoords;
      vec3  Tangent;
      vec3  Bitangent;
      int   m_BoneIDs[HOLO_MAX_BONE_INFLUENCE];
      float m_Weights[HOLO_MAX_BONE_INFLUENCE];
  };
  using GlVertexBuffer = GlBuffer<GL_ARRAY_BUFFER, GlVertex, GL_STATIC_DRAW>;
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
      shared_ptr<GlBufferElements> EBO;

      void SetupMesh();
  };
}