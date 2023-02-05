#pragma once
#include <GL/glew.h>
#include <memory>
namespace holo {
  template<GLenum BufferType, typename DataType, GLenum DataUsage>
  class GlBuffer {
    public:
      using sPtr = std::shared_ptr<GlBuffer>;
      static sPtr Create() {
        GLuint id;
        glGenBuffers(1, &id);
        return sPtr{ new GlBuffer(id) };
      };

    private:
      GlBuffer(GLuint id)
        : ID{ id }
        , Kind{ BufferType }
        , Usage{ DataUsage } {};
      GLuint const ID;
      GLenum const Kind;
      GLenum const Usage;

    public:
      ~GlBuffer() { glDeleteBuffers(1, &ID); };
      void Bind() { glBindBuffer(Kind, ID); };
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

  class GlProgram {
    public:
      using sPtr = std::shared_ptr<GlProgram>;
      const GLuint ID;
      static sPtr  Create();

    private:
      GlProgram();

    public:
      ~GlProgram();
      void        Attach(GlShader::sPtr);
      bool        Link();
      bool        GetLinkStatus();
      std::string GetLog();
      GLint       GetAttribLocation(std::string);
      void        Use();
      static void StopUse();
  };
}