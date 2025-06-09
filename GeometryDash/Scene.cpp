/**********************************************************************************
// Scene (C�digo Fonte)
// 
// Cria��o:     16 Mar 2012
// Atualiza��o: 28 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para gerenciar o cen�rio do jogo.
//
//              Um gerenciador de cena � respons�vel por guardar os objetos
//              da cena, atualizando-os e desenhando-os de forma mais pr�tica.
//              Ele pode ser usado tamb�m para outras tarefas que impliquem em
//              percorrer a lista de objetos, como detec��o de colis�o.
//
**********************************************************************************/

#include "Scene.h"
#include "Object.h"
#include "Engine.h"
#include <limits>

// ---------------------------------------------------------------------------------

Scene::Scene()
{

}

// ---------------------------------------------------------------------------------

Scene::~Scene()
{
    // remove da mem�ria os objetos est�ticos
    for (auto obj : statics)
        delete obj;

    // remove da mem�ria os objetos em movimento
    for (auto obj : moving)
        delete obj;
}

// ---------------------------------------------------------------------------------


void Scene::Add(Object* obj, int type)
{
    // insere novo objeto na cena
    if (type == STATIC)
        statics.push_back(obj);
    else
        moving.push_back(obj);
}

// ---------------------------------------------------------------------------------

void Scene::Remove(Object* obj, int type)
{
    // remove objeto da cena
    if (type == STATIC)
        statics.remove(obj);
    else
        moving.remove(obj);
}

// ---------------------------------------------------------------------------------

void Scene::Remove()
{
    // remove objeto da cena
    if (processing == STATIC)
        statics.remove(*it);
    else
        moving.remove(*it);
}

// ---------------------------------------------------------------------------------

void Scene::Delete(Object* obj, int type)
{
    toDelete.push_back(ObjectDel{ obj, type });
}

// ---------------------------------------------------------------------------------

void Scene::Delete()
{
    toDelete.push_back(ObjectDel{ *it, processing });
}

// ---------------------------------------------------------------------------------

uint Scene::Size()
{
    return uint(moving.size() + statics.size());
}

// ---------------------------------------------------------------------------------

void Scene::ClearDeleted()
{
    // remove objetos duplicados
    toDelete.sort();
    toDelete.unique();

    for (const auto & [obj, type] : toDelete)
    {
        // libera mem�ria ocupada pelo objeto
        delete obj;

        // remove objeto da cena
        if (type == STATIC)
            statics.remove(obj);
        else
            moving.remove(obj);
    }

    // esvazia a lista 
    toDelete.clear();
}

// ---------------------------------------------------------------------------------

void Scene::Update()
{
    // atualiza todos os objetos est�ticos
    processing = STATIC;
    for (it = statics.begin(); it != statics.end(); ++it)
        (*it)->Update();

    // atualiza todos os objetos em movimento
    processing = MOVING;
    for (it = moving.begin(); it != moving.end(); ++it)
        (*it)->Update();

    ClearDeleted();
}

// ---------------------------------------------------------------------------------

void Scene::Draw()
{
    // desenha todos os objetos est�ticos
    processing = STATIC;
    for (it = statics.begin(); it != statics.end(); ++it)
        (*it)->Draw();

    // desenha todos os objetos em movimento
    processing = MOVING;
    for (it = moving.begin(); it != moving.end(); ++it)
        (*it)->Draw();
}

// ---------------------------------------------------------------------------------

void Scene::DrawBBox()
{
    // inicia desenho de pixels
    Engine::renderer->BeginPixels();

    // desenha bounding box dos objetos est�ticos
    for (const auto& obj : statics)
    {
        if (obj->BBox())
            Engine::renderer->Draw(obj->BBox(), 0xffff00ff);
    }

    // desenha bounding box dos objetos em movimento
    for (const auto& obj : moving)
    {
        if (obj->BBox())
            Engine::renderer->Draw(obj->BBox(), 0xffff00ff);
    }

    // finaliza desenho de pixels
    Engine::renderer->EndPixels();
}

// ---------------------------------------------------------------------------------

void Scene::Begin()
{
    // aponta para o primeiro elemento de cada lista
    its = statics.begin();
    itm = moving.begin();
    processing = STATIC;
}

// ---------------------------------------------------------------------------------

Object * Scene::Next()
{
    // se apontador aponta para objeto v�lido
    if (its != statics.end())
    {
        // passa ao pr�ximo objeto
        // guarda apontador para o anterior
        it = its++;
        return *it;
    }
    else
        if (itm != moving.end())
        {
            processing = MOVING;
            it = itm++;
            return *it;
        }
        else
            // chegou ao fim das listas
            return nullptr;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point* p, Point* q)
{
    // se as coordenadas inteiras s�o iguais 
    if (int(p->X()) == int(q->X()) && int(p->Y()) == int(q->Y()))
        return true;

    // caso contr�rio n�o h� colis�o
    return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point * p, Rect * r)
{
    // se as coordenadas  do ponto est�o dentro do ret�ngulo
    if (p->X() >= r->Left() && p->X() <= r->Right())
        if (p->Y() >= r->Top() && p->Y() <= r->Bottom())
            return true;

    // caso contr�rio n�o h� colis�o
    return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Point * p, Circle * c)
{
    // se a dist�ncia entre o ponto e o centro do c�rculo
    // for menor que o raio do c�rculo ent�o h� colis�o
    if (p->Distance(Point(c->CenterX(), c->CenterY())) <= c->radius)
        return true;
    else
        return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Rect * ra, Rect * rb)
{
    // verificando sobreposi��o no eixo x
    bool overlapX = (rb->Left() <= ra->Right() && ra->Left() <= rb->Right());

    // verificando sobreposi��o no eixo y
    bool overlapY = (rb->Top() <= ra->Bottom() && ra->Top() <= rb->Bottom());

    // existe colis�o se h� sobreposi��o nos dois eixos
    return overlapX && overlapY;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Rect * r, Circle * c)
{
    // encontra o ponto do ret�ngulo mais pr�ximo do centro do c�rculo
    float px, py;

    // eixo x
    if (c->CenterX() < r->Left())
        px = r->Left();
    else
        if (c->CenterX() > r->Right())
            px = r->Right();
        else
            px = c->CenterX();

    // eixo y
    if (c->CenterY() < r->Top())
        py = r->Top();
    else
        if (c->CenterY() > r->Bottom())
            py = r->Bottom();
        else
            py = c->CenterY();

    // verifica se h� colis�o entre este ponto e o c�rculo
    Point point(px, py);
    return Collision(&point, c);
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Circle * ca, Circle * cb)
{
    // deltas podem ser negativos se a subtra��o � feita na ordem errada
    // levando essa possibilidade em conta � melhor pegar os valores absolutos
    float deltaX = abs(ca->CenterX() - cb->CenterX());
    float deltaY = abs(ca->CenterY() - cb->CenterY());

    // calcule a dist�ncia entre os centros dos c�rculos
    float distance = float(sqrt(double(deltaX) * double(deltaX) + double(deltaY) * double(deltaY)));

    // se a dist�ncia � menor que a soma dos raios
    // existe colis�o entre os c�rculos
    if (distance <= (ca->radius + cb->radius))
        return true;

    // nenhum colis�o detectada
    return false;
}

bool Scene::Collision(Poly* c, Point* p)
{
    return false;
}

float dotProduct(const Point& a, const Point& b) {
    return a.X() * b.X() + a.Y() * b.Y();
}

Point getNormal(Point& v1, Point& v2) {
    return { -(v2.Y() - v1.Y()), v2.X() - v1.X()};
}

float project(const Point vertex, const Point& axis) {
    float len = sqrt(dotProduct(axis, axis));
    return dotProduct(vertex, axis) / len;
}

bool a(Point axis, Poly* c, Poly* polygonB) {
    float minA = FLT_MAX;
    float maxA = -FLT_MAX;
    float minB = FLT_MAX;
    float maxB = -FLT_MAX;

    for (int i = 0; i < c->vertexCount; i++) {
        Point p = c->vertexList[i];
        p.Translate(c->X(), c->Y());
        float projection = project(p, axis);
        minA = min(minA, projection);
        maxA = max(maxA, projection);
    }

    for (int i = 0; i < polygonB->vertexCount; i++) {
        float projection = project(polygonB->vertexList[i], axis);
        minB = min(minB, projection);
        maxB = max(maxB, projection);
    }

    if (!(maxA >= minB && minA <= maxB)) {
        return true; // Separating axis found, no collision 
    }
    return false;
}

bool Scene::Collision(Poly* c, Rect* p)
{   
    Point points[4] = {
        { p->Left(), p->Top() },
        { p->Left(), p->Bottom() },
        { p->Right(), p->Bottom() },
        { p->Right(), p->Top() }
    };
    Poly rect = Poly(points, 4);
    
    // Test axes from c
    for (int i = 0; i < c->vertexCount; ++i) {
        Point v1 = c->vertexList[i];
        Point v2 = c->vertexList[(i + 1) % c->vertexCount];
        v1.Translate(c->X(), c->Y());
        v2.Translate(c->X(), c->Y());
        if (a(getNormal(v1, v2), c, &rect)) return false;
    }

    // Test axes from rect 
    for (int i = 0; i < rect.vertexCount; ++i) {
        Point v1 = rect.vertexList[i];
        Point v2 = rect.vertexList[(i + 1) % rect.vertexCount];
        if (a(getNormal(v1, v2), c, &rect)) return false;
    }

    return true; // No separating axis found, collision detected

}

bool Scene::Collision(Poly* c, Circle* p)
{
    return false;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Mixed * m, Geometry * s)
{
    bool collision = false;

    // percorra lista at� achar uma colis�o
    auto i = m->shapes.begin();

    while (!collision && i != m->shapes.end())
    {
        switch ((*i)->Type())
        {
            // Point
        case POINT_T:
            switch (s->Type())
            {
            case POINT_T:     collision = Collision((Point*)(*i), (Point*)s);  break;
            case CIRCLE_T:    collision = Collision((Point*)(*i), (Circle*)s); break;
            case RECTANGLE_T: collision = Collision((Point*)(*i), (Rect*)s);   break;
            case MIXED_T:     collision = Collision((Point*)(*i), (Mixed*)s);  break;
            case POLYGON_T:   collision = Collision((Point*)(*i), (Poly*)s);   break;
            }
            break;

            // Circle
        case CIRCLE_T:
            switch (s->Type())
            {
            case POINT_T:     collision = Collision((Circle*)(*i), (Point*)s);  break;
            case CIRCLE_T:    collision = Collision((Circle*)(*i), (Circle*)s); break;
            case RECTANGLE_T: collision = Collision((Circle*)(*i), (Rect*)s);   break;
            case POLYGON_T:   collision = Collision((Circle*)(*i), (Poly*)s);   break;
            case MIXED_T:     collision = Collision((Circle*)(*i), (Mixed*)s);  break;
            }
            break;

            // Rectangle
        case RECTANGLE_T:
            switch (s->Type())
            {
            case POINT_T:     collision = Collision((Rect*)(*i), (Point*)s);  break;
            case CIRCLE_T:    collision = Collision((Rect*)(*i), (Circle*)s); break;
            case RECTANGLE_T: collision = Collision((Rect*)(*i), (Rect*)s);   break;
            case POLYGON_T:   collision = Collision((Rect*)(*i), (Poly*)s);   break;
            case MIXED_T:     collision = Collision((Rect*)(*i), (Mixed*)s);  break;
            }
            break;

            // Mixed
        case MIXED_T:
            collision = Collision((Mixed*)(*i), s);
            break;
        }

        // passa para a pr�xima geometria da forma mista
        ++i;
    }

    return collision;
}

// --------------------------------------------------------------------------------

bool Scene::Collision(Object* oa, Object* ob)
{
    // um dos objetos n�o tem bounding box
    if (!(oa->BBox() && ob->BBox()))
        return false;

    switch (oa->BBox()->Type())
    {
        // Point    
    case POINT_T:

        switch (ob->BBox()->Type())
        {
        case POINT_T:
            // Point && Point
            return Collision((Point*)oa->BBox(), (Point*)ob->BBox());

        case CIRCLE_T:
            // Point && Circle
            return Collision((Point*)oa->BBox(), (Circle*)ob->BBox());

        case RECTANGLE_T:
            // Point && Rectangle
            return Collision((Point*)oa->BBox(), (Rect*)ob->BBox());

        case POLYGON_T:
            // Point && Polygon
            return Collision((Point*)oa->BBox(), (Poly*)ob->BBox());

        case MIXED_T:
            // Point && Mixed
            return Collision(oa->BBox(), (Mixed*)ob->BBox());

        default:
            // Point && Unknown
            return false;
        }

        // Circle    
    case CIRCLE_T:

        switch (ob->BBox()->Type())
        {
        case POINT_T:
            // Circle && Point
            return Collision((Circle*)oa->BBox(), (Point*)ob->BBox());

        case CIRCLE_T:
            // Circle && Circle
            return Collision((Circle*)oa->BBox(), (Circle*)ob->BBox());

        case RECTANGLE_T:
            // Circle && Rectangle
            return Collision((Circle*)oa->BBox(), (Rect*)ob->BBox());

        case POLYGON_T:
            // Circle && Polygon
            return Collision((Circle*)oa->BBox(), (Poly*)ob->BBox());

        case MIXED_T:
            // Circle && Mixed
            return Collision(oa->BBox(), (Mixed*)ob->BBox());

        default:
            // Circle && Unknown
            return false;
        }

        // Rectangle
    case RECTANGLE_T:

        switch (ob->BBox()->Type())
        {
        case POINT_T:
            // Rectangle && Point
            return Collision((Rect*)oa->BBox(), (Point*)ob->BBox());

        case CIRCLE_T:
            // Rectangle && Circle
            return Collision((Rect*)oa->BBox(), (Circle*)ob->BBox());

        case RECTANGLE_T:
            // Rectangle && Rectangle
            return Collision((Rect*)oa->BBox(), (Rect*)ob->BBox());

        case POLYGON_T:
            // Rectangle && Polygon
            return Collision((Rect*)oa->BBox(), (Poly*)ob->BBox());

        case MIXED_T:
            // Rectangle && Mixed
            return Collision(oa->BBox(), (Mixed*)ob->BBox());

        default:
            // Rectangle && Unknown
            return false;
        }

        // Mixed
    case MIXED_T:
        // Mixed && Geometry
        return Collision((Mixed*)oa->BBox(), ob->BBox());


        // Unknown
    default:
        return false;
    }
}

// ---------------------------------------------------------------------------------

void Scene::CollisionDetection()
{
    // iteradores para as listas
    list<Object*>::iterator start, end;

    // limpa lista de colis�es
    collisions.clear();

    // -------------------
    // Detec��o da colis�o
    // -------------------

    // se existe pelo menos dois objetos que se movem, teste a colis�o entre eles
    if (moving.size() >= 2)
    {
        // pega iterador para �ltimo elemento da lista
        end = moving.end();
        end--;

        // testa colis�o entre todos os pares de objetos que se movem
        for (auto i = moving.begin(); i != end; ++i)
        {
            start = i;

            // j inicia no segundo elemento da lista
            for (auto j = ++start; j != moving.end(); ++j)
            {
                if (Collision(*i, *j))
                    collisions.push_back(ObjectPair(*i, *j));
            }
        }
    }

    // testa colis�o entre objetos que se movem e objetos est�ticos
    for (auto i : moving)
    {
        for (auto j : statics)
        {
            if (Collision(i, j))
                collisions.push_back(ObjectPair(i, j));
        }
    }

    // --------------------
    // Resolu��o da colis�o
    // --------------------

    if (!collisions.empty())
    {
        for (auto [a,b] : collisions)
        {
            a->OnCollision(b);
            b->OnCollision(a);
        }
    }

    ClearDeleted();
}

// --------------------------------------------------------------------------------
