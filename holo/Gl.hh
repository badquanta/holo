#pragma once
/** \todo REMOVE */
#include <holo/sdl/Primitives.hh>
#include <holo/gl/Errors.hh>
#include <holo/gl/base.hh>
#include <holo/gl/math.hh>
namespace holo {
  /**
   * \see https://www.opengl.org/sdk/docs/tutorials/CodeColony/vertexarrays.php
   */
  class GlVertexArray {
    public:
      using sPtr = std::shared_ptr<GlVertexArray>;
      static sPtr  Create();
      GLuint const ID;

    private:
      explicit GlVertexArray(GLuint);

    public:
      virtual ~GlVertexArray();
      /** static global bind, stack unaffected, last updated.*/
      GLuint        Bind() const;
      static GLuint Bind(GLuint);
  };
  /** Manage the lifetime of a texture via shared_ptr */
  class GlTexture {
    public:
      using sPtr = std::shared_ptr<GlTexture>;
      /** Create an empty texture. */
      static sPtr  Create();
      /** Create a new texture from SDL Surface data.*/
      static sPtr  Create(SdlSurfacePtr);
      /** Load a texture from the hard drive.*/
      static sPtr  Load(std::string);
      /** Read-only ID*/
      const GLuint ID;

    private:
      /** inaccessible, use `Create()` */
      GlTexture(GLuint);

    public:
      ~GlTexture();
      void Bind() const;
      void Set(SdlSurfacePtr);
      void Set(SdlSurfacePtr, GLint ws, GLint wt, GLint mf, GLint Mf);
  };
  template<GLenum BufferType, typename DataType, GLenum DataUsage>
  class GlBuffer {
    public:
      using sPtr = std::shared_ptr<GlBuffer>;
      static sPtr Create() {
        GLuint id;
        glGenBuffers(1, &id);
        return sPtr{ new GlBuffer(id) };
      };
      static sPtr Create(std::vector<DataType>& data) {
        sPtr created{ Create() };
        created->Data(data);
        return created;
      };

    private:
      explicit GlBuffer(GLuint id)
        : ID{ id }
        , Kind{ BufferType }
        , Usage{ DataUsage } {};
      GLuint const ID;
      GLenum const Kind;
      GLenum const Usage;

    public:
      ~GlBuffer() { glDeleteBuffers(1, &ID); };
      void Bind() { glBindBuffer(Kind, ID); };
      void Data(std::vector<DataType>& data) { Data(data.size(), data.data()); }
      void Data(int length, const DataType data[]) {
        Bind();
        glBufferData(Kind, length * sizeof(DataType), data, Usage);
      };
  };
  class GlShader {
    public:
      using sPtr = std::shared_ptr<GlShader>;
      static sPtr Load(GLenum, const std::string&);
      static sPtr Create(GLenum);
      static sPtr Create(GLenum, const GLchar*);

    private:
      GlShader(GLenum type);

    public:
      ~GlShader();
      void         SetSource(const GLchar*);
      void         LoadSource(std::string);
      bool         GetCompileStatus();
      bool         Compile();
      std::string  GetLog();
      GLuint const ID;
      GLenum const Type;
  };

  class GlSlProgram {
    public:
      using sPtr = std::shared_ptr<GlSlProgram>;
      const GLuint                        ID;
      static std::shared_ptr<GlSlProgram> Create();
      static std::shared_ptr<GlSlProgram> Build(string vertSrc, string fragSrc);

    private:
      GlSlProgram();

    public:
      ~GlSlProgram();
      void           Attach(GlShader::sPtr);
      bool           Link();
      bool           GetLinkStatus();
      bool           Validate();
      bool           GetValidateStatus();
      int            GetAttributeCount();
      int            GetUniformCount();
      int            GetMaxAttributeLength();
      vector<string> GetAttributeList();
      string         GetAttributeName(int index);
      string         GetLog();
      GLint          GetAttribLocation(const std::string&);
      GLint          GetUniformLocation(const std::string&);
      void           Use();
      static void    StopUse();

      void SetBool(const string&, bool);
      void SetInt(const string&, int);
      void SetFloat(const string&, float);
      void SetVec2(const string&, const vec2&);
      void SetVec2(const string&, float, float);
      void SetVec3(const string&, const vec3&);
      void SetVec3(const string&, float, float, float);
      void SetVec4(const string&, const vec4&);
      void SetVec4(const string&, float, float, float, float);
      void SetMat2(const string&, const mat2&);
      void SetMat3(const string&, const mat3&);
      void SetMat4(const string&, const mat4&);
  };
}