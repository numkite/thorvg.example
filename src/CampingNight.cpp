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
    static tvg::Shape* pine(float x, float y, float scale)
    {
        auto tree = tvg::Shape::gen();
        tree->moveTo(x, y);
        tree->lineTo(x + 35.0f * scale, y - 58.0f * scale);
        tree->lineTo(x + 17.0f * scale, y - 58.0f * scale);
        tree->lineTo(x + 50.0f * scale, y - 108.0f * scale);
        tree->lineTo(x + 31.0f * scale, y - 108.0f * scale);
        tree->lineTo(x + 65.0f * scale, y - 158.0f * scale);
        tree->lineTo(x + 99.0f * scale, y - 108.0f * scale);
        tree->lineTo(x + 80.0f * scale, y - 108.0f * scale);
        tree->lineTo(x + 113.0f * scale, y - 58.0f * scale);
        tree->lineTo(x + 95.0f * scale, y - 58.0f * scale);
        tree->lineTo(x + 130.0f * scale, y);
        tree->close();
        tree->fill(18, 49, 54);
        return tree;
    }

    static tvg::Shape* rock(float x, float y, float scale)
    {
        auto stone = tvg::Shape::gen();
        stone->moveTo(x, y);
        stone->cubicTo(x + 3.0f * scale, y - 18.0f * scale,
                       x + 16.0f * scale, y - 25.0f * scale,
                       x + 30.0f * scale, y - 20.0f * scale);
        stone->cubicTo(x + 43.0f * scale, y - 17.0f * scale,
                       x + 51.0f * scale, y - 8.0f * scale,
                       x + 55.0f * scale, y);
        stone->close();
        stone->fill(82, 87, 91);
        return stone;
    }

    bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override
    {
        auto scene = tvg::Scene::gen();

        // Night sky
        auto sky = tvg::Shape::gen();
        sky->appendRect(0, 0, 800, 600);
        auto skyFill = tvg::LinearGradient::gen();
        skyFill->linear(0, 0, 0, 600);
        tvg::Fill::ColorStop skyStops[3] = {
            {0.0f, 12, 18, 48, 255},
            {0.62f, 45, 57, 88, 255},
            {1.0f, 111, 91, 96, 255}
        };
        skyFill->colorStops(skyStops, 3);
        sky->fill(skyFill);
        scene->add(sky);

        // Crescent moon: a dark circle overlaps a pale circle.
        auto moon = tvg::Shape::gen();
        moon->appendCircle(650, 105, 48, 48);
        moon->fill(255, 241, 187);
        scene->add(moon);

        auto moonShade = tvg::Shape::gen();
        moonShade->appendCircle(671, 87, 48, 48);
        moonShade->fill(16, 23, 53);
        scene->add(moonShade);

        // Small stars made from circles and crossed strokes.
        const float stars[][3] = {
            {90, 82, 2.5f}, {170, 135, 2.0f}, {275, 65, 3.0f},
            {382, 122, 2.0f}, {493, 71, 2.5f}, {744, 170, 2.0f}
        };
        for (const auto& star : stars) {
            auto dot = tvg::Shape::gen();
            dot->appendCircle(star[0], star[1], star[2], star[2]);
            dot->fill(255, 238, 180);
            scene->add(dot);
        }

        auto brightStar = tvg::Shape::gen();
        brightStar->moveTo(545, 132);
        brightStar->lineTo(545, 152);
        brightStar->moveTo(535, 142);
        brightStar->lineTo(555, 142);
        brightStar->strokeFill(255, 239, 184);
        brightStar->strokeWidth(2.5f);
        brightStar->strokeCap(tvg::StrokeCap::Round);
        scene->add(brightStar);

        // Two mountain layers create depth.
        auto farMountain = tvg::Shape::gen();
        farMountain->moveTo(0, 385);
        farMountain->lineTo(0, 305);
        farMountain->lineTo(125, 190);
        farMountain->lineTo(235, 300);
        farMountain->lineTo(350, 215);
        farMountain->lineTo(500, 350);
        farMountain->lineTo(620, 245);
        farMountain->lineTo(800, 365);
        farMountain->lineTo(800, 385);
        farMountain->close();
        farMountain->fill(46, 58, 76);
        scene->add(farMountain);

        auto nearMountain = tvg::Shape::gen();
        nearMountain->moveTo(0, 430);
        nearMountain->lineTo(0, 355);
        nearMountain->lineTo(155, 260);
        nearMountain->lineTo(290, 380);
        nearMountain->lineTo(445, 285);
        nearMountain->lineTo(610, 405);
        nearMountain->lineTo(720, 320);
        nearMountain->lineTo(800, 375);
        nearMountain->lineTo(800, 430);
        nearMountain->close();
        nearMountain->fill(29, 45, 57);
        scene->add(nearMountain);

        auto ground = tvg::Shape::gen();
        ground->moveTo(0, 420);
        ground->cubicTo(180, 390, 290, 450, 445, 425);
        ground->cubicTo(600, 400, 690, 425, 800, 410);
        ground->lineTo(800, 600);
        ground->lineTo(0, 600);
        ground->close();
        ground->fill(15, 39, 38);
        scene->add(ground);

        scene->add(pine(28, 490, 1.15f));
        scene->add(pine(675, 485, 0.95f));
        scene->add(pine(605, 470, 0.62f));

        // Tent body and its entrance flap.
        auto tent = tvg::Shape::gen();
        tent->moveTo(165, 505);
        tent->lineTo(285, 340);
        tent->lineTo(425, 505);
        tent->close();
        auto tentFill = tvg::LinearGradient::gen();
        tentFill->linear(165, 340, 425, 505);
        tvg::Fill::ColorStop tentStops[2] = {
            {0.0f, 231, 119, 67, 255},
            {1.0f, 151, 54, 48, 255}
        };
        tentFill->colorStops(tentStops, 2);
        tent->fill(tentFill);
        tent->strokeFill(96, 43, 42);
        tent->strokeWidth(3);
        tent->strokeJoin(tvg::StrokeJoin::Round);
        scene->add(tent);

        auto entrance = tvg::Shape::gen();
        entrance->moveTo(285, 340);
        entrance->lineTo(285, 505);
        entrance->lineTo(365, 505);
        entrance->close();
        entrance->fill(85, 43, 48);
        scene->add(entrance);

        auto tentLight = tvg::Shape::gen();
        tentLight->moveTo(285, 365);
        tentLight->lineTo(285, 505);
        tentLight->lineTo(347, 505);
        tentLight->close();
        tentLight->fill(255, 195, 104, 205);
        scene->add(tentLight);

        // Logs behind the fire.
        auto leftLog = tvg::Shape::gen();
        leftLog->appendRect(485, 522, 122, 18, 8, 8);
        leftLog->fill(91, 53, 36);
        leftLog->rotate(14);
        scene->add(leftLog);

        auto rightLog = tvg::Shape::gen();
        rightLog->appendRect(497, 548, 122, 18, 8, 8);
        rightLog->fill(91, 53, 36);
        rightLog->rotate(-14);
        scene->add(rightLog);

        // A cubic Bezier path forms a soft, asymmetric flame.
        auto flame = tvg::Shape::gen();
        flame->moveTo(550, 535);
        flame->cubicTo(512, 503, 548, 473, 552, 448);
        flame->cubicTo(578, 478, 596, 493, 580, 521);
        flame->cubicTo(573, 536, 561, 542, 550, 535);
        flame->close();
        auto flameFill = tvg::RadialGradient::gen();
        flameFill->radial(552, 508, 56, 552, 516, 5);
        tvg::Fill::ColorStop flameStops[3] = {
            {0.0f, 255, 245, 153, 255},
            {0.48f, 255, 157, 54, 255},
            {1.0f, 219, 61, 42, 255}
        };
        flameFill->colorStops(flameStops, 3);
        flame->fill(flameFill);
        scene->add(flame);

        auto innerFlame = tvg::Shape::gen();
        innerFlame->moveTo(552, 529);
        innerFlame->cubicTo(535, 512, 551, 493, 556, 482);
        innerFlame->cubicTo(571, 505, 570, 520, 552, 529);
        innerFlame->close();
        innerFlame->fill(255, 235, 139);
        scene->add(innerFlame);

        scene->add(rock(438, 558, 0.75f));
        scene->add(rock(624, 568, 0.62f));

        canvas->add(scene);
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
