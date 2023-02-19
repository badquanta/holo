/** \todo notices
 * \file
 * \see https://learnopengl.com/Model-Loading/Model
 * \see https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/model.h
 */
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <holo/gl/Model.hh>
#include <holo/sdl/GlTexture.hh>
namespace holo {
  GlModel::GlModel(string path, bool g)
    : gammaCorrection{ g } {
    LoadModel(path);
  }

  void GlModel::Draw(shared_ptr<GlSlProgram> shader) {
    for (auto mesh : meshes) {
      mesh.Draw(shader);
    }
  }

  void GlModel::LoadModel(string path) {
    Assimp::Importer importer;
    const aiScene*   scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
              aiProcess_CalcTangentSpace
    );
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      throw runtime_error(string(" AI SCENE_FLAGS_INCOMPLETE ") + importer.GetErrorString());
    }
    directory = filesystem::path(path).parent_path();
    ProcessNode(scene->mRootNode, scene);
  }

  void GlModel::ProcessNode(aiNode* node, const aiScene* scene) {
    for (uint32_t i = 0; i < node->mNumMeshes; i++) {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(ProcessMesh(mesh, scene));
    }
    for (uint32_t i = 0; i < node->mNumChildren; i++) {
      ProcessNode(node->mChildren[i], scene);
    }
  }
  GlMesh GlModel::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    vector<GlVertex>              vertices;
    vector<uint32_t>              indices;
    vector<shared_ptr<GlTexture>> textures;
    for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
      GlVertex vertex;
      auto makeVec3 = [](auto something) { return vec3{ something.x, something.y, something.z }; };
      vertex.Position = makeVec3(mesh->mVertices[i]);
      if (mesh->HasNormals()) {
        vertex.Normal = makeVec3(mesh->mNormals[i]);
      }
      auto makeVec2 = [](auto something) { return vec2{ something.x, something.y }; };
      // texture cords
      if (mesh->mTextureCoords[0]) {
        // a vertex can contain up to 8 different texture coordinates. We thus make the assumption
        // that we won't use models where a vertex can have multiple texture coordinates so we
        // always take the first set (0).
        vertex.TexCoords = makeVec2(mesh->mTextureCoords[0][i]);
        // tangent
        vertex.Tangent   = makeVec3(mesh->mTangents[i]);
        // bitangent
        vertex.Bitangent = makeVec3(mesh->mBitangents[i]);
      } else {
        vertex.TexCoords = vec2(0.0f, 0.0f);
      }
      vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the
    // corresponding vertex indices.

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for (uint32_t j = 0; j < face.mNumIndices; j++) {
        indices.push_back(face.mIndices[j]);
      }
    }
    // process materials
    aiMaterial*                   material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
    vector<shared_ptr<GlTexture>> diffuseMaps =
      LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<shared_ptr<GlTexture>> specularMaps =
      LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    vector<shared_ptr<GlTexture>> normalMaps =
      LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    vector<shared_ptr<GlTexture>> heightMaps =
      LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return GlMesh(vertices, indices, textures);
  }

  vector<shared_ptr<GlTexture>> GlModel::LoadMaterialTextures(
    aiMaterial* mat, aiTextureType type, string typeName
  ) {
    vector<shared_ptr<GlTexture>> textures;
    for (uint32_t i = 0; i < mat->GetTextureCount(type); i++) {
      aiString str;
      mat->GetTexture(type, i, &str);
      // check if texture was loaded before and if so, continue to next iteration: skip loading a
      // new texture
      bool skip = false;
      for (uint32_t j = 0; j < textures_loaded.size(); j++) {
        if (std::strcmp(textures_loaded[j]->path.data(), str.C_Str()) == 0) {
          textures.push_back(textures_loaded[j]);
          skip = true;
          break;
        }
      }
      if (!skip) {
        shared_ptr<GlTexture> texture{
          SdlGlTexture::Load(str.C_Str(), { ".png", ".jpg" }, {}, { this->directory.string() })
        };
        texture->type = typeName;
        texture->path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture);
      }
    }
    return textures;
  }
}