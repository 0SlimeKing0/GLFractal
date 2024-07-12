#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"

CLASS_PTR(Context);
class Context {
    public:
        static ContextUPtr Create();
        void Render() const;
    private:
        Context() {};
        bool Init();

        unsigned int shaderProgram;
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
};

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif