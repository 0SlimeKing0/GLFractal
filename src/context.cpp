#include <spdlog/spdlog.h>

#include "context.h"
#include "shader.h"

ContextUPtr Context::Create() {
    ContextUPtr context = ContextUPtr(new Context());
    if (!context->Init()) {
        SPDLOG_ERROR("Failed to initialize context.");
        return nullptr;
    }

    return std::move(context);
}

void Context::Render() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Context::Init() {
    float vertices[] = {
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
        1.0f, -1.0f, 0.0f, 1.0f, -1.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, -1.0f, -1.0f,  // bottom left
        -1.0f,  1.0f, 0.0f, -1.0f, 1.0f,  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);   
    glBindVertexArray(VAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/mandelbrot.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader)
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertShader->Get());
    glAttachShader(shaderProgram, fragShader->Get());
    glLinkProgram(shaderProgram);

    glDeleteShader(vertShader->Get());
    glDeleteShader(fragShader->Get());

    int screenRatio = glGetUniformLocation(shaderProgram, "screenRatio");

    glUseProgram(shaderProgram);
    glUniform1f(screenRatio, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

    return true;
}