#include "timer.h"
#include "player.h"
#include "enemy.h"
#include "rect.h"
#include "enemybox.h"
#include <vector>
#include <map>
#include <utility>


#define WIDTH 1024
#define HEIGHT 768
#define CIRCLE 0
#define RECTANGLE 1

#define ENEMIES 3

#define pow2(x) x * x

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Player *player;
vector<Enemy> enemies;
map<int, EnemyBox> enemy_boxes;
vector<Rect> flooring;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 2.5f;

bool up_flag = false;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(auto floor: flooring) floor.draw(VP);
    player->draw(VP);
    for(auto &enemy: enemies) enemy.draw(VP);
    for(auto &box: enemy_boxes) (box.second).draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);

    // player left or right
    if (left) player->xspeed += 0.001;
    else if (right) player->xspeed -= 0.001;
    else if(player->xspeed > 0.8 * -0.01 && player->xspeed < 0.8 * 0.01) player->xspeed = 0;
    else {
        if (player->xspeed < 0)
            player->xspeed += 0.01;
        else if (player->xspeed > 0)
            player->xspeed -= 0.01;
    }

    // player jump
    if (up == GLFW_PRESS && !up_flag) up_flag = true, player->yspeed = 0.2;
    if (up == GLFW_RELEASE) up_flag = false;
}

// spawn a new enemy when one is deleted
void spawn_enemy() {
    enemies.push_back(Enemy(0, 0, COLOR_RED, 0.4f));
    // randomly add enemy boxes
    if(rand() % ENEMIES < ENEMIES / 2)
        enemy_boxes.insert(make_pair(enemies.back().id,
         EnemyBox(enemies.back(), COLOR_LOG)));
}

// delete an enemy with a given id
bool delete_enemy(int id) {
    for(vector<Enemy>::iterator enemy =  enemies.begin(); enemy != enemies.end(); enemy++)
        if(enemy->id == id) {
            enemies.erase(enemy);
            Enemy::enemy_count--;

            auto it = enemy_boxes.erase(id);
            if(it) EnemyBox::box_count--;

            // randomly spawn new enemies
            if(rand() % 2) spawn_enemy();
            return true;
        }
    return false;
}

int tick_elements() {
    player->tick();
    for(auto &enemy : enemies) enemy.tick();
    for(auto &box: enemy_boxes) (box.second).tick();
    for(auto &enemy: enemies)
        if (detect_collision(player->bounding_box(), enemy.bounding_box())) {
            cout<<rand() % 100<<" Circle collision"<<endl;
            if(player->position.y < enemy.position.y) {
                cout<<"\n\nCOLLIDED Enemy  Circle: "<<enemy.id<<endl;
                player->lives--;
                cout<<"\nLives : "<<player->lives<<endl;
            }
            else {
                cout<<"\n\nKILLED ENEMY Circle"<<enemy.id<<endl;
                int fac = (player->position.x < enemy.position.x)? -2 : 2;
                player->xspeed *= fac * 1.03f;
                if(player->yspeed > 0) player->yspeed *= 1.15f;
                else player->yspeed = 0.2f;
                delete_enemy(enemy.id);
            }
            break;
        }
    for(auto &box: enemy_boxes)
        if (detect_collision(player->bounding_box(), box.second.bounding_box())) {
            cout<<rand() % 100<<" Rectangle collision"<<endl;
            if(player->position.y < box.second.position.y) {
                cout<<"\n\nCOLLIDED Enemy  Rectangle: "<<box.second.id<<endl;
                player->lives--;
                cout<<"\nLives : "<<player->lives<<endl;
            }
            else {
                cout<<"\n\nKILLED ENEMY Rectangle"<<box.second.id<<endl;
                delete_enemy(box.second.id);
                player->xspeed += 1.05f * player->xspeed * sin(box.second.rotation);
                if(player->yspeed > 0) player->yspeed *= 1.15f;
                else player->yspeed = 0.2f;
            }
            break;
        }
    if(!player->lives || !enemies.size()) {
        cout<<((!player->lives)? "Game Over!" : "Winner!")<<endl;
        return true;
    }
    return false;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    player = new Player(0, 0, COLOR_BLACK);
    flooring.push_back(Rect(0.0f, -2.5f / 2 - player->radius / 2.0f, 10.0f, 5.0f, COLOR_GROUND_1));
    flooring.push_back(Rect(0.0f, -player->radius, 10.0f, 0.8f, COLOR_GREEN));
    for(int enemy = 1; enemy <= ENEMIES; enemy++) spawn_enemy();
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = WIDTH;
    int height = HEIGHT;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps

            // OpenGL Draw commands
            draw();

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            bool game_stat = tick_elements();
            tick_input(window);

            // OpenGL Draw commands
            draw();


            if(game_stat) break;

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    if(b.role == CIRCLE)
        return (pow2(fabs(a.x - b.x)) + pow2(fabs(a.y - b.y))) < pow2(a.radius + b.radius);
    else if(b.role == RECTANGLE) {
        auto dimen = b.size;
        double diag = sqrt(pow2(dimen.first) + pow2(dimen.second)) / 2.0f,
        x_tol = diag * cos(b.rotation), y_tol = diag * sin(b.rotation);
        return (a.x > b.x - x_tol && a.x < b.x + x_tol) ||
            (a.y > b.y - y_tol && a.y < b.y - y_tol);
    }
}

void reset_screen() {
    float top    = screen_center_y + 5 / screen_zoom;
    float bottom = screen_center_y - 5 / screen_zoom;
    float left   = screen_center_x - 5 / screen_zoom;
    float right  = screen_center_x + 5 / screen_zoom;
    float ratio = WIDTH / HEIGHT;
    Matrices.projection = glm::ortho(left * ratio, right * ratio, bottom, top, 0.1f, 500.0f);
}
