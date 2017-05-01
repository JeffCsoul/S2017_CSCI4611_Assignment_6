#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Box2D/Box2D.h>
#include <vector>

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

    b2World *world;
    b2Body *body;

    Circle() {}
    Circle(vec2 center, float radius, b2World *external_world, bool fixed) {
        this->center = center;
        this->radius = radius;
        this->world = external_world;
        b2BodyDef bodydef;
        if (fixed)
          bodydef.type = b2_staticBody;
        else
          bodydef.type = b2_dynamicBody;
        this->body = this->world->CreateBody(&bodydef);

        b2CircleShape circleshape;
        circleshape.m_p.Set(this->center.x, this->center.y);
        circleshape.m_radius = this->radius;

        b2FixtureDef fixdef;
        fixdef.shape = &circleshape;
        fixdef.friction = 0.2;
        fixdef.restitution = 0.4;
        fixdef.density = 0.4;
        this->body->CreateFixture(&fixdef);
    }

    vec2 getLocalPoint(vec2 worldPoint) {
      b2Vec2 localp = this->body->GetLocalPoint(b2Vec2(worldPoint.x,
                                                       worldPoint.y));
      return vec2(localp.x, localp.y);
    }

    bool contains(vec2 worldPoint) {
        // return glm::length(worldPoint - center) <= radius;
       return glm::length(getLocalPoint(worldPoint) - center) <= radius;
    }
    mat4 getTransformation() {
      b2Vec2 pos = body->GetPosition();
      float angle = body->GetAngle();
      return glm::translate(vec3(pos.x, pos.y, 0)) *
             glm::rotate(angle,vec3(0, 0, 1));
    }
    void destroy() {
      this->world->DestroyBody(body);
    }
};

class Box {
public:
    vec2 center;
    vec2 size;

    b2World *world;
    b2Body *body;

    Box() {}
    Box(vec2 center, vec2 size, b2World *external_world, bool fixed) {
        this->center = center;
        this->size = size;
        this->world = external_world;
        b2BodyDef bodydef;
        if (fixed)
          bodydef.type = b2_staticBody;
        else
          bodydef.type = b2_dynamicBody;
        bodydef.position.Set(center.x, center.y);
        this->body = this->world->CreateBody(&bodydef);

        b2PolygonShape polygonshape;
        polygonshape.SetAsBox(size.x / 2, size.y / 2);

        b2FixtureDef fixdef;
        fixdef.shape = &polygonshape;
        fixdef.density = 0.2;
        fixdef.friction = 0.4;
        fixdef.restitution = 0.4;
        body->CreateFixture(&fixdef);
    }

    vec2 getLocalPoint(vec2 worldPoint) {
      b2Vec2 localp = this->body->GetLocalPoint(b2Vec2(worldPoint.x,
                                                       worldPoint.y));
      return vec2(localp.x, localp.y);
    }

    bool contains(vec2 worldPoint) {
        vec2 d = getLocalPoint(worldPoint);
        return (abs(d.x) <= size.x/2 && abs(d.y) <= size.y/2);
    }
    mat4 getTransformation() {
      b2Vec2 pos = body->GetPosition();
      float angle = body->GetAngle();
      return glm::translate(vec3(pos.x, pos.y, 0)) *
             glm::rotate(angle, vec3(0, 0, 1)) *
             glm::translate(vec3(-center, 0));
    }
    void destroy() {
      this->world->DestroyBody(body);
    }
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
        this->body = this->world->CreateBody(&bodydef);

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
