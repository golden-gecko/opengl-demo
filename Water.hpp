#pragma once

class Water
{
public:
    float scale;
    float level;

    float waveHeightMin;
    float waveHeightMax;

    float waveSpeed;
    float waveHeight;

    Water();

    void render(float time);
};
