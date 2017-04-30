#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <glm/glm.hpp>
#include <vector>
#include <Box2D/Box2D.h>

using namespace std;
using glm::vec2;

// TODO: Modify these classes to keep track of the corresponding Box2D
// bodies. Feel free to add helpful methods like
//     mat4 getTransformation()
// and
//     vec2 getLocalPoint(vec2 worldPoint).

class Circle {
public:
    vec2 center;
    float radius;
    Circle() {}
    Circle(vec2 center, float radius) {
        this->center = center;
        this->radius = radius;
    }
    bool contains(vec2 worldPoint) {
        return glm::length(worldPoint - center) <= radius;
    }
    void destroy() {}
};

class Box {
public:
    vec2 center;
    vec2 size;
    Box() {}
    Box(vec2 center, vec2 size) {
        this->center = center;
        this->size = size;
    }
    bool contains(vec2 worldPoint) {
        vec2 d = worldPoint - center;
        return (abs(d.x) <= size.x/2 && abs(d.y) <= size.y/2);
    }
    void destroy() {}
};

class Polyline {
public:
    vector<vec2> vertices;
    b2World *world;
    b2Body *body;

    Polyline() {}
    Polyline(vector<vec2> vertices, b2World *external_world) {
        this->vertices = vertices;
        this->world = external_world;
        b2BodyDef bodydef;
        bodydef.type = b2_staticBody;
        this->body = this->world->createBody(&bodydef);

        vector<b2Vec2> v;
        for (int i = 0; i < vertices.size(); i++)
          v.push_back(b2Vec2(vertices[i].x, vertices[i].y));
        b2ChainShape chainshape;
        chainshape.CreateChain(&v[0], v.size());

        b2FixtureDef fixdef;
        fixdef.shape = & chainshape;
        this->body->CreateFixture(&fixdef);
    }
    void destroy() {
      this->world->DestroyBody(body);
    }
};

#endif
