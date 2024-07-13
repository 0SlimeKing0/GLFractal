#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "cam2d.h"

CLASS_PTR(Context);
class Context {
    public:
        static ContextUPtr Create(Cam2DUPtr& _cam);
        void Render() const;
    private:
        Context() {};
        bool Init();

        Cam2DUPtr cam;

        unsigned int camPosLocation;
        unsigned int shaderProgram;
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
};

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif