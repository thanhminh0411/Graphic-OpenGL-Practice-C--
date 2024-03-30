#include "Draw2d.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>

void Draw2d::bresenhamLine(Point2d a, Point2d b, GLFWwindow &window)
{

    while (!glfwWindowShouldClose(&window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);

        int x1 = a.getX();
        int y1 = a.getY();
        int x2 = b.getX();
        int y2 = b.getY();

        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            glBegin(GL_POINTS);
            glVertex2i(x1, y1);
            glEnd();

            if (x1 == x2 && y1 == y2)
            {
                break;
            }

            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y1 += sy;
            }
        }

        // Kiểm tra xem phím ESC có được nhấn không để thoát khỏi vòng lặp
        if (glfwGetKey(&window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            break; // Thoát khỏi vòng lặp nếu phím ESC được nhấn
        }
        glfwSwapBuffers(&window);
        glfwPollEvents();
    }
}
void Draw2d::drawCircle(Point2d o, int radius, GLFWwindow &window)
{
    while (!glfwWindowShouldClose(&window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);

        int x = 0;
        int y = radius;
        int d = 3 - 2 * radius;

        while (x <= y)
        {
            // Vẽ các điểm tương đương trên 8 octant
            glBegin(GL_POINTS);
            glVertex2i(o.getX() + x, o.getY() + y);
            glVertex2i(o.getX() - x, o.getY() + y);
            glVertex2i(o.getX() + x, o.getY() - y);
            glVertex2i(o.getX() - x, o.getY() - y);
            glVertex2i(o.getX() + y, o.getY() + x);
            glVertex2i(o.getX() - y, o.getY() + x);
            glVertex2i(o.getX() + y, o.getY() - x);
            glVertex2i(o.getX() - y, o.getY() - x);
            glEnd();

            if (glfwGetKey(&window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                break;
            }

            if (d < 0)
            {
                d += 4 * x + 6;
            }
            else
            {
                d += 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
        if (glfwGetKey(&window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            break;
        }
        glfwSwapBuffers(&window);
        glfwPollEvents();

        // Thêm phần kiểm tra kí tự được nhấn tại đây nếu cần
    }
}

void Draw2d::drawEllipse(Point2d o, int a, int b, GLFWwindow &window)
{
    while (!glfwWindowShouldClose(&window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);

        // Tính các giá trị ban đầu cho thuật toán
        int x = 0, y = b;
        int e2 = b * b - a * a * b + (a * a) / 4;

        // Vẽ 4 điểm đối xứng ban đầu
        glBegin(GL_POINTS);
        glVertex2i(o.getX() + x, o.getY() + y);
        glVertex2i(o.getX() - x, o.getY() + y);
        glVertex2i(o.getX() + x, o.getY() - y);
        glVertex2i(o.getX() - x, o.getY() - y);
        glEnd();

        // Đường Ellip chính
        while (b * b * x <= a * a * y)
        {
            // Vẽ 4 điểm đối xứng
            glBegin(GL_POINTS);
            glVertex2i(o.getX() + x, o.getY() + y);
            glVertex2i(o.getX() - x, o.getY() + y);
            glVertex2i(o.getX() + x, o.getY() - y);
            glVertex2i(o.getX() - x, o.getY() - y);
            glEnd();
            x++;
            if (e2 < 0)
                e2 += b * b * (2 * x + 3);
            else
            {
                y--;
                e2 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            }
        }

        // Đường Ellip phần còn lại
        while (y >= 0)
        {
            // Vẽ 4 điểm đối xứng
            glBegin(GL_POINTS);
            glVertex2i(o.getX() + x, o.getY() + y);
            glVertex2i(o.getX() - x, o.getY() + y);
            glVertex2i(o.getX() + x, o.getY() - y);
            glVertex2i(o.getX() - x, o.getY() - y);
            glEnd();

            y--;
            if (e2 > 0)
                e2 += a * a * (-2 * y + 3);
            else
            {
                x++;
                e2 += a * a * (-2 * y + 3) + b * b * (2 * x + 2);
            }
        }
        if (glfwGetKey(&window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            break;
        }
        glfwSwapBuffers(&window);
        glfwPollEvents();

        // Thêm phần kiểm tra kí tự được nhấn tại đây nếu cần
    }
}
