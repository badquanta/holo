#include <holo/gl/Mesh.hh>
#include <holo/boostPrimitives.hh>
namespace holo {
  GlMesh::GlMesh(vector<GlVertex> v, vector<uint32_t> i, vector<shared_ptr<GlTexture>> t)
    : vertices{ v }
    , indices{ i }
    , textures{ t } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    SetupMesh();
  }

  void GlMesh::Draw(shared_ptr<GlSlProgram> shader) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    uint32_t diffuseNr = 1, specularNr = 1, normalNr = 1, heightNr = 1;
    for (uint32_t i = 0; i < textures.size(); i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      string number;
      /** @todo GlTextures may need a type field?? **/
      string typeName = textures[i]->type;
      if (typeName == "texture_diffuse") {
        number = std::to_string(diffuseNr++);
      } else if (typeName == "texture_specular") {
        number = std::to_string(specularNr++);
      } else if (typeName == "texture_normal") {
        number = std::to_string(normalNr++);
      } else if (typeName == "texture_height") {
        number = std::to_string(heightNr++);
      } else {
        BOOST_LOG_TRIVIAL(error) << "INVALID TYPE NAME: "  << typeName;
      }
      shader->SetInt((typeName + number), i);
      textures[i]->Bind();
    }
    // draw mesh
    VAO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);
    VAO->Unbind();
    glActiveTexture(GL_TEXTURE0);
  }

  void GlMesh::SetupMesh() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    VAO = GlVertexArray::Create();
    VAO->Bind();
    VBO = GlVertexBuffer::Create(vertices);
    EBO = GlBufferElements::Create(indices);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GlVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
      1, 3, GL_FLOAT, GL_FALSE, sizeof(GlVertex), (void*)offsetof(GlVertex, Normal)
    );
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
      2, 2, GL_FLOAT, GL_FALSE, sizeof(GlVertex), (void*)offsetof(GlVertex, TexCoords)
    );
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(
      3, 3, GL_FLOAT, GL_FALSE, sizeof(GlVertex), (void*)offsetof(GlVertex, Tangent)
    );
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(
      4, 3, GL_FLOAT, GL_FALSE, sizeof(GlVertex), (void*)offsetof(GlVertex, Bitangent)
    );
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(GlVertex), (void*)offsetof(GlVertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(
      6, 4, GL_FLOAT, GL_FALSE, sizeof(GlVertex), (void*)offsetof(GlVertex, m_Weights)
    );
    glBindVertexArray(0);
  }
}