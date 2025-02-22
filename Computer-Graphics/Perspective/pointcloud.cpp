#include "pointcloud.h"

pointcloud::pointcloud() {
    initStyles();
    std::srand(std::time(nullptr));
    for (int i = 0; i < this->point_count; i++) {
        coordinate* temp_coord = new coordinate();
        temp_coord->x = (double)((double)(std::rand() % 80000)  / 1000) - 40.0;
        temp_coord->y = 15.5 + (double)((double)(std::rand() % 15000) / 1000);
        temp_coord->z = (double)((double)(std::rand() % 80000) / 1000) - 40.0;
        this->coords.push_back(temp_coord);
    }
}

void pointcloud::initStyles() {
    std::vector<color*> s;
    s.push_back(new color({0.969, 1, 0.678})); // light yellow
    s.push_back(new color({0.988, 0.753, 0.749})); // light red
    s.push_back(new color({0.749, 0.988, 0.988})); // light cyan
    s.push_back(new color({0.973, 0.749, 0.988})); // light magenta
    s.push_back(new color({0.769, 0.988, 0.749})); // light green
    this->colors.push_back(s);
}

void pointcloud::render(pointcloud_style s) {
    //  Save transformation
    glPushMatrix();
    int cnt = 0;
    bool flag = false;
    switch (s) {
        case POINTCLOUD_WHITE:
            glBegin(GL_POINTS);
            glColor3f(1.0, 1.0, 1.0);
            for (auto i : this->coords)
                glVertex3f(i->x, i->y, i->z);
            glEnd();
            break;
        default:
            glBegin(GL_POINTS);
            for (auto i : this->coords) {
                if ((cnt % 10) == 0) {glColor3f(this->colors.at(0).at(4)->x, this->colors.at(0).at(4)->y, this->colors.at(0).at(4)->z); flag = true;}
                else if ((cnt % 5) == 0) {glColor3f(this->colors.at(0).at(3)->x, this->colors.at(0).at(3)->y, this->colors.at(0).at(3)->z); flag = true;}
                else if ((cnt % 4) == 0) {glColor3f(this->colors.at(0).at(2)->x, this->colors.at(0).at(2)->y, this->colors.at(0).at(2)->z); flag = true;}
                else if ((cnt % 3) == 0) {glColor3f(this->colors.at(0).at(1)->x, this->colors.at(0).at(1)->y, this->colors.at(0).at(1)->z); flag = true;}
                else if ((cnt % 2) == 0) {glColor3f(this->colors.at(0).at(0)->x, this->colors.at(0).at(0)->y, this->colors.at(0).at(0)->z); flag = true;}
                glVertex3f(i->x, i->y, i->z);
                if (flag) {glColor3f(1.0, 1.0, 1.0); flag = false; }
                cnt++;
            }
            glEnd();
    }
    glPopMatrix();
} 