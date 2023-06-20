#ifndef SOKOBAN_SPRITE_H
#define SOKOBAN_SPRITE_H

#include "basemodel.h"


class Sprite : public BaseModel {
public:
    // This is a rectangle:
    // (x,y) ->  0 --- 1
    //           | \   |
    //           |  \  |
    //           |   \ |
    //           3 --- 2 <- (z,w)
    inline Sprite(const glm::vec4& pos, const glm::vec4& uv, std::shared_ptr<TextureAsset> texture)
            : BaseModel({
                     TextureVertex(glm::vec3{pos.x, pos.y, 0.f}, glm::vec2{uv.x, uv.y}), // 0
                     TextureVertex(glm::vec3{pos.z, pos.y, 0.f}, glm::vec2{uv.z, uv.y}), // 1
                     TextureVertex(glm::vec3{pos.z, pos.w, 0.f}, glm::vec2{uv.z, uv.w}), // 2
                     TextureVertex(glm::vec3{pos.x, pos.w, 0.f}, glm::vec2{uv.x, uv.w}) }, // 3
                     {0, 1, 2, 0, 2, 3},
                     texture) { }
};


#endif //SOKOBAN_SPRITE_H
