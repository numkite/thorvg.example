/*
 * Copyright (c) 2020 - 2026 ThorVG project. All rights reserved.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Example.h"

/************************************************************************/
/* ThorVG Drawing Contents                                              */
/************************************************************************/

struct UserExample : tvgexam::Example
{
    struct Bubble
    {
        tvg::Shape* shape;
        float x;
        float startY;
        float speed;
        float delay;
    };

    tvg::Scene* orangeFish = nullptr;
    tvg::Scene* yellowFish = nullptr;
    vector<Bubble> bubbles;

    tvg::Scene* makeFish(uint8_t r, uint8_t g, uint8_t b, float size)
    {
        auto fish = tvg::Scene::gen();

        // Body
        auto body = tvg::Shape::gen();
        body->appendCircle(0, 0, 52.0f * size, 30.0f * size);
        auto bodyFill = tvg::LinearGradient::gen();
        bodyFill->linear(-50.0f * size, -20.0f * size,
                         45.0f * size, 20.0f * size);
        tvg::Fill::ColorStop bodyStops[2] = {
            {0.0f, r, g, b, 255},
            {1.0f,
             uint8_t(r > 35 ? r - 35 : 0),
             uint8_t(g > 35 ? g - 35 : 0),
             uint8_t(b > 35 ? b - 35 : 0), 255}
        };
        bodyFill->colorStops(bodyStops, 2);
        body->fill(bodyFill);
        fish->add(body);

        // Tail
        auto tail = tvg::Shape::gen();
        tail->moveTo(-45.0f * size, 0);
        tail->lineTo(-82.0f * size, -30.0f * size);
        tail->lineTo(-76.0f * size, 0);
        tail->lineTo(-82.0f * size, 30.0f * size);
        tail->close();
        tail->fill(r, g, b);
        fish->add(tail);

        // Top fin
        auto fin = tvg::Shape::gen();
        fin->moveTo(-12.0f * size, -25.0f * size);
        fin->cubicTo(0, -48.0f * size,
                     25.0f * size, -42.0f * size,
                     30.0f * size, -20.0f * size);
        fin->close();
        fin->fill(r, g, b, 210);
        fish->add(fin);

        auto eye = tvg::Shape::gen();
        eye->appendCircle(30.0f * size, -7.0f * size,
                          6.0f * size, 6.0f * size);
        eye->fill(250, 250, 245);
        fish->add(eye);

        auto pupil = tvg::Shape::gen();
        pupil->appendCircle(32.0f * size, -7.0f * size,
                            2.5f * size, 2.5f * size);
        pupil->fill(25, 36, 45);
        fish->add(pupil);
        return fish;
    }

    void addSeaweed(tvg::Scene* scene, float x, float height,
                    uint8_t r, uint8_t g, uint8_t b)
    {
        auto weed = tvg::Shape::gen();
        weed->moveTo(x, 560);
        weed->cubicTo(x - 25, 520, x + 25, 490, x, 560 - height);
        weed->strokeFill(r, g, b);
        weed->strokeWidth(10);
        weed->strokeCap(tvg::StrokeCap::Round);
        scene->add(weed);

        auto leaf = tvg::Shape::gen();
        leaf->moveTo(x - 2, 520);
        leaf->cubicTo(x + 22, 500, x + 34, 507, x + 39, 518);
        leaf->strokeFill(r, g, b);
        leaf->strokeWidth(7);
        leaf->strokeCap(tvg::StrokeCap::Round);
        scene->add(leaf);
    }

    bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override
    {
        auto background = tvg::Shape::gen();
        background->appendRect(0, 0, w, h);
        auto water = tvg::LinearGradient::gen();
        water->linear(0, 0, 0, h);
        tvg::Fill::ColorStop waterStops[3] = {
            {0.0f, 89, 195, 220, 255},
            {0.55f, 34, 137, 173, 255},
            {1.0f, 13, 72, 105, 255}
        };
        water->colorStops(waterStops, 3);
        background->fill(water);
        canvas->add(background);

        auto floor = tvg::Shape::gen();
        floor->moveTo(0, 520);
        floor->cubicTo(180, 490, 305, 550, 470, 515);
        floor->cubicTo(620, 485, 710, 520, 800, 500);
        floor->lineTo(800, 600);
        floor->lineTo(0, 600);
        floor->close();
        floor->fill(224, 190, 122);
        canvas->add(floor);

        auto plants = tvg::Scene::gen();
        addSeaweed(plants, 95, 130, 20, 112, 87);
        addSeaweed(plants, 145, 95, 26, 132, 92);
        addSeaweed(plants, 690, 145, 18, 104, 80);
        addSeaweed(plants, 735, 105, 31, 129, 91);
        canvas->add(plants);

        auto rock = tvg::Shape::gen();
        rock->moveTo(310, 548);
        rock->cubicTo(315, 500, 350, 475, 392, 490);
        rock->cubicTo(425, 503, 439, 526, 446, 548);
        rock->close();
        rock->fill(94, 110, 116);
        canvas->add(rock);

        auto smallRock = tvg::Shape::gen();
        smallRock->appendCircle(485, 545, 39, 22);
        smallRock->fill(124, 133, 132);
        canvas->add(smallRock);

        orangeFish = makeFish(245, 132, 76, 1.0f);
        yellowFish = makeFish(248, 205, 86, 0.72f);
        canvas->add(orangeFish);
        canvas->add(yellowFish);

        const float bubbleData[][5] = {
            {190, 500, 7, 38, 0.0f},
            {220, 470, 4, 46, 1.1f},
            {585, 510, 6, 42, 0.4f},
            {620, 460, 9, 35, 1.8f},
            {650, 520, 4, 50, 2.5f},
            {550, 430, 5, 40, 3.0f}
        };

        for (const auto& data : bubbleData) {
            auto bubble = tvg::Shape::gen();
            bubble->appendCircle(0, 0, data[2], data[2]);
            bubble->fill(205, 246, 250, 35);
            bubble->strokeFill(215, 250, 252, 185);
            bubble->strokeWidth(2);
            canvas->add(bubble);
            bubbles.push_back({bubble, data[0], data[1], data[3], data[4]});
        }

        return update(canvas, 0);
    }

    bool update(tvg::Canvas* canvas, uint32_t elapsed) override
    {
        const auto seconds = elapsed * 0.001f;

        // fmodf() moves each fish continuously from left to right and wraps it.
        auto orangeX = -90.0f + fmodf(seconds * 78.0f, 980.0f);
        auto orangeY = 255.0f + sinf(seconds * 1.15f) * 12.0f;
        orangeFish->translate(orangeX, orangeY);

        auto yellowX = -90.0f + fmodf(seconds * 52.0f + 420.0f, 980.0f);
        auto yellowY = 365.0f + sinf(seconds * 0.9f + 1.0f) * 9.0f;
        yellowFish->translate(yellowX, yellowY);

        // fmodf() wraps each bubble back to the bottom after it reaches the top.
        for (auto& bubble : bubbles) {
            auto rise = fmodf((seconds + bubble.delay) * bubble.speed, 470.0f);
            bubble.shape->translate(bubble.x, bubble.startY - rise);
        }

        canvas->update();
        return true;
    }
};

/************************************************************************/
/* Entry Point                                                          */
/************************************************************************/

int main(int argc, char **argv)
{
    return tvgexam::main(new UserExample, argc, argv, false, 800, 600);
}