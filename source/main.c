#include <3ds.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv)
{
    gfxInitDefault();

    PrintConsole topScreen, bottomScreen;

    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);

    consoleSelect(&bottomScreen);
    printf(" \x1b[44;37m.------------------------------------.\x1b[40;37m\n");
    printf(" \x1b[44;37m|  3DS Donut v1.0                    |\x1b[40;37m\n");
    printf(" \x1b[44;37m|  (Press Start to Quit)             |\x1b[40;37m\n");
	printf(" \x1b[44;37m|  Made by Metakabe                  |\x1b[40;37m\n");
	printf(" \x1b[44;37m|  <metakabe.nekoweb.org>            |\x1b[40;37m\n");
    printf(" \x1b[44;37m|  Based on the original donut.c     |\x1b[40;37m\n");
    printf(" \x1b[44;37m|  by Andy Sloane <andy@a1k0n.net>   |\x1b[40;37m\n");
    printf(" \x1b[44;37m|  And on the Wii Port               |\x1b[40;37m\n");
    printf(" \x1b[44;37m|  by jornmann <jornmann@duck.com>   |\x1b[40;37m\n");
    printf(" \x1b[44;37m'------------------------------------'\x1b[40;37m\n");

    const int width = 50;
    const int height = 24;
    char b[width * height];
    float z[width * height];

    float A = 0, B = 0;

    while (aptMainLoop())
    {
        hidScanInput();
        if (hidKeysDown() & KEY_START) break;

        memset(b, ' ', sizeof(b));
        memset(z, 0, sizeof(z));

        for (float j = 0; j < 6.28f; j += 0.07f) {
            for (float i = 0; i < 6.28f; i += 0.02f) {
                float c = sinf(i), d = cosf(j), e = sinf(A), f = sinf(j);
                float g = cosf(A), h = d + 2;
                float D = 1 / (c * h * e + f * g + 4);
                float l = cosf(i), m = cosf(B), n = sinf(B);
                float t = c * h * g - f * e;
                int x = (int)(width / 2 + (width / 2.2f) * D * (l * h * m - t * n));
                int y = (int)(height / 2 + (height / 2.2f) * D * (l * h * n + t * m));
                int o = x + width * y;
                int N = (int)(8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n));
                if (y >= 0 && y < height && x >= 0 && x < width && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        consoleSelect(&topScreen);
        consoleClear();
        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? b[k] : '\n');
        }

        A += 0.04f;
        B += 0.08f;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
