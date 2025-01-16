#include "Include/Raycaster.hpp"

int GetTextureX(int x) {
    int NewX = Global::Map::TextureSize - x - 1;
    if (x >= 0 && x < Global::Map::TextureSize) return NewX;
    return 0;
}

sf::Color GetFogColor(const sf::Color &TextureColor, float Distance) {
    float FogFactor = 1.0f - std::min(1.0f, Distance * Global::Player::FogDensity);
    sf::Color FogColor(
        sf::Uint8(TextureColor.r * FogFactor),
        sf::Uint8(TextureColor.g * FogFactor),
        sf::Uint8(TextureColor.b * FogFactor)
    );
    return FogColor;
}

Raycaster::Raycaster() {
    Width = static_cast<int>(Global::Window::Width / Global::Window::Resize);
    Height = static_cast<int>(Global::Window::Height / Global::Window::Resize);

    BufferPixels = new sf::Uint8[Width * Height * 4];
    BufferTexture.create(Width, Height);
    BufferSprite.setTexture(BufferTexture);
    BufferSprite.setScale(sf::Vector2f(Global::Window::Resize, Global::Window::Resize));
}

Raycaster::~Raycaster() = default;

void Raycaster::FloorAndCeilingCast() {
    for (int y = 0; y < Height; y++) {
        float rayDirX0 = m_Player.GetDirection().x - m_Player.GetPlane().x;
        float rayDirY0 = m_Player.GetDirection().y - m_Player.GetPlane().y;
        float rayDirX1 = m_Player.GetDirection().x + m_Player.GetPlane().x;
        float rayDirY1 = m_Player.GetDirection().y + m_Player.GetPlane().y;

        int p = y - Height / 2;
        float posZ = 0.5 * Height;
        float rowDistance = posZ / p;
        rowDistance = Clamp(rowDistance, 0.0f, Global::Player::RenderDistance);

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / Width;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / Width;

        float floorX = m_Player.GetPosition().x + rowDistance * rayDirX0;
        float floorY = m_Player.GetPosition().y + rowDistance * rayDirY0;

        for (int x = 0; x < Width; x++) {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            int tx = (int)(Global::Map::TextureSize * (floorX - cellX)) & (Global::Map::TextureSize - 1);
            int ty = (int)(Global::Map::TextureSize * (floorY - cellY)) & (Global::Map::TextureSize - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            // Floor
            sf::Color tcolor = GetFogColor(GetTileReference('p')->Texture.getPixel(GetTextureX(tx), ty), rowDistance);
            Buffer[y][x] = (rowDistance == Global::Player::RenderDistance) ? sf::Color::Black.toInteger() : tcolor.toInteger();

            // Ceiling
            tcolor = GetFogColor(GetTileReference('c')->Texture.getPixel(GetTextureX(tx), ty), rowDistance);
            Buffer[Height - y - 1][x] = (rowDistance == Global::Player::RenderDistance) ? sf::Color::Black.toInteger() : tcolor.toInteger();
        }
    }
}

void Raycaster::WallCast() {
    for (int x = 0; x < Width; x++) {
        double cameraX = 2 * x / double(Width) - 1;
        double rayPosX = m_Player.GetPosition().x;
        double rayPosY = m_Player.GetPosition().y;
        double rayDirX = m_Player.GetDirection().x + m_Player.GetPlane().x * cameraX;
        double rayDirY = m_Player.GetDirection().y + m_Player.GetPlane().y * cameraX;

        int mapX = int(rayPosX);
        int mapY = int(rayPosY);

        double sideDistX;
        double sideDistY;

        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (rayPosX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (rayPosY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (!GetTileReference(GetTile(mapX, mapY))->IsSprite && GetTile(mapX, mapY) != '.') hit = 1;
        }

        if (side == 0) perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
        else perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
        perpWallDist = Clamp(perpWallDist, 0.0f, Global::Player::RenderDistance);

        int lineHeight = abs(int(Height / perpWallDist));

        int drawStart = ((Height / 2) - lineHeight / 2);
        if (drawStart < 0) drawStart = 0;
        int drawEnd = ((Height / 2) + lineHeight / 2);
        if (drawEnd >= Height) drawEnd = Height;

        int texNum = GetTile(mapX, mapY);
        Tile *ref = GetTileReference(texNum);

        double wallX;
        if (side == 0) wallX = m_Player.GetPosition().y + perpWallDist * rayDirY;
        else wallX = m_Player.GetPosition().x + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        int texX = int(wallX * double(Global::Map::TextureSize));
        if (side == 0 && rayDirX > 0) texX = Global::Map::TextureSize - texX - 1;
        if (side == 1 && rayDirY < 0) texX = Global::Map::TextureSize - texX - 1;

        double step = 1.0 * Global::Map::TextureSize / lineHeight;
        double texPos = (drawStart - Height / 2 + lineHeight / 2) * step;

        for (int y = drawStart; y < drawEnd; y++) {
            int texY = (int)texPos & (Global::Map::TextureSize - 1);
            texPos += step;

            sf::Color tcolor = GetFogColor(ref->Texture.getPixel(GetTextureX(texX), texY), perpWallDist / 1.15f);
            if (side == 1) {
                tcolor.r /= 1.25f;
                tcolor.g /= 1.25f;
                tcolor.b /= 1.25f;
            }

            Buffer[y][x] = (perpWallDist == Global::Player::RenderDistance) ? sf::Color::Black.toInteger() : tcolor.toInteger();
        }
        BufferZ[x] = perpWallDist;
    }
}

void Raycaster::SpriteCast() {
    SpriteOrder.clear();
    SpriteDistance.clear();

    for (int i = 0; i < Sprites.size(); i++) {
        SpriteOrder.push_back(i);
        SpriteDistance.push_back(
            (m_Player.GetPosition().x - Sprites[i].GetPosition().x) *
            (m_Player.GetPosition().x - Sprites[i].GetPosition().x) +
            (m_Player.GetPosition().y - Sprites[i].GetPosition().y) *
            (m_Player.GetPosition().y - Sprites[i].GetPosition().y)
        );
    }

    SortSprites();

    for (int i = 0; i < Sprites.size(); i++) {
        double spriteX = Sprites[SpriteOrder[i]].GetPosition().x - m_Player.GetPosition().x;
        double spriteY = Sprites[SpriteOrder[i]].GetPosition().y - m_Player.GetPosition().y;

        double invDet = 1.0 / (m_Player.GetPlane().x * m_Player.GetDirection().y - m_Player.GetDirection().x * m_Player.GetPlane().y);

        double transformX = invDet * (m_Player.GetDirection().y * spriteX - m_Player.GetDirection().x * spriteY);
        double transformY = invDet * (-m_Player.GetPlane().y * spriteX + m_Player.GetPlane().x * spriteY);

        int spriteScreenX = int((Width / 2) * (1 + transformX / transformY));

        int spriteHeight = abs(int(Height / (transformY)));

        int drawStartY = -spriteHeight / 2 + Height / 2;
        if (drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + Height / 2;
        if (drawEndY >= Height) drawEndY = Height;

        int spriteWidth = abs(int(Height / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= Width) drawEndX = Width;

        for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
            int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * Global::Map::TextureSize / spriteWidth) / 256;

            if (transformY > 0 && stripe > 0 && stripe < Width && transformY < BufferZ[stripe]) {
                for (int y = drawStartY; y < drawEndY; y++) {
                    int d = (y) * 256 - Height * 128 + spriteHeight * 128;
                    int texY = ((d * Global::Map::TextureSize) / spriteHeight) / 256;

                    sf::Color tcolor;
                    float Distance;
                    try {
                        char Symbol = Sprites[SpriteOrder[i]].GetSymbol();
                        Tile *Reference = GetTileReference(Symbol);

                        Distance = (SpriteDistance[i] / 5.0f);
                        tcolor = Reference->Texture.getPixel(GetTextureX(texX), texY);
                    } catch (...) {
                        tcolor = sf::Color::Transparent;
                    }

                    if (tcolor.a != 0) Buffer[y][stripe] = GetFogColor(tcolor, Distance).toInteger();
                }
            }
        }
    }
}

void Raycaster::SortSprites() {
    std::vector<std::pair<double, int>> spr(Sprites.size());
    for (int i = 0; i < Sprites.size(); i++) {
        spr[i].first = SpriteDistance[i];
        spr[i].second = SpriteOrder[i];
    }

    std::sort(spr.begin(), spr.end());
    for (int i = 0; i < Sprites.size(); i++) {
        SpriteDistance[i] = spr[Sprites.size() - i - 1].first;
        SpriteOrder[i] = spr[Sprites.size() - i - 1].second;
    }
}

void Raycaster::Raycast() {
    FloorAndCeilingCast();
    WallCast();
    SpriteCast();
}

void Raycaster::Render(sf::RenderWindow& Window) {
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            Buffer[y][x] = 0;
        }
    }

    Raycast();

    int i = 0;
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            BufferPixels[i] = sf::Color(Buffer[y][x]).r;
            BufferPixels[i + 1] = sf::Color(Buffer[y][x]).g;
            BufferPixels[i + 2] = sf::Color(Buffer[y][x]).b;
            BufferPixels[i + 3] = sf::Color(Buffer[y][x]).a;
            i += 4;
        }
    }

    BufferTexture.update(BufferPixels);
    Window.draw(BufferSprite);
}
