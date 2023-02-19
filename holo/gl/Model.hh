#pragma once
/** @todo notices */
#include <holo/gl/Mesh.hh>
#include <assimp/scene.h>
namespace holo {
  class GlModel {
    public:
      vector<shared_ptr<GlTexture>> textures_loaded;
      vector<GlMesh>                meshes;
      filesystem::path              directory;
      bool                          gammaCorrection;

      GlModel(string modelPath, bool gamma = false);
      void Draw(shared_ptr<GlSlProgram> shader);

    private:
      void                          LoadModel(string path);
      void                          ProcessNode(aiNode* node, const aiScene* scene);
      GlMesh                        ProcessMesh(aiMesh* mesh, const aiScene* scene);
      vector<shared_ptr<GlTexture>> LoadMaterialTextures(
        aiMaterial* mat, aiTextureType type, string typeName
      );
  };
}