#pragma once
#include <GL/glew.h>
#include <holo/sdl/Primitives.hh>

namespace holo {
  class GlVertexArray {
    public:
      using sPtr = std::shared_ptr<GlVertexArray>;
      static sPtr  Create();
      GLuint const ID;

    private:
      explicit GlVertexArray(GLuint);

    public:
      virtual ~GlVertexArray();
      void Bind() const;
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
      const GLuint ID;
      static sPtr  Create();

    private:
      GlSlProgram();

    public:
      ~GlSlProgram();
      void                     Attach(GlShader::sPtr);
      bool                     Link();
      bool                     GetLinkStatus();
      bool                     Validate();
      bool                     GetValidateStatus();
      int                      GetAttributeCount();
      int                      GetUniformCount();
      int                      GetMaxAttributeLength();
      std::vector<std::string> GetAttributeList();
      std::string              GetAttributeName(int index);
      std::string              GetLog();
      GLint                    GetAttribLocation(const std::string&);
      GLint                    GetUniformLocation(const std::string&);
      void                     Use();
      static void              StopUse();

      void Set(const std::string&, bool);
      void Set(const std::string&, int);
      void Set(const std::string&, float);
  };
}