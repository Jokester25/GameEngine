#include "Engine.h";


using namespace nu;
using namespace std;

struct Transform 
{
    Vector2 position;
    float rotation;
    float scale;

};

class Actor
{
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform{ transform } {}

    void Update(float dt) {
        
        m_transform.position += (m_velocity * dt);
            
        m_transform.position.x = Wrap(0.0f, 1280.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Draw(const Renderer& renderer) const{
        renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

   const Transform& GetTransform() { return m_transform; }
   void SetPosition(Vector2& position) { m_transform.position = position; }
   void SetRotation(float rotation) { m_transform.rotation = rotation; }
   void SetScale(float scale) { m_transform.scale = scale; }

   const Vector2 GetVelocity() { return m_velocity; }
   void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }

protected:
    Transform m_transform;
    Vector2 m_velocity{ 0, 0 };
};



int main()
{   
    //INITIALIZATION
    Renderer renderer;
    const float SCREEN_W = 1280.0f;
	const float SCREEN_H = 1024.0f;
    renderer.Initialize("Game Engine", SCREEN_W, SCREEN_H);

    Input input;
    input.Initialize();

    Time time;

    Actor player{ Transform{Vector2{640.0f, 512.0f}, 0.0f, 50.0f} };

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 400.0f;

    std::vector<Vector2> points;


    //Main Loop
    bool quit = false;
    while (!quit) {
        //Update
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        //engine
        input.Update();
        time.Tick();
       
        if (input.GetButtonDown(Input::MouseButton::Left)) {
            Vector2 mousePos = input.GetMousePosition();
            if (points.empty()) {
                points.push_back(input.GetMousePosition());

            }
            else {
                Vector2 v = points.back() - input.GetMousePosition();

                if (v.Length() > 10.0f) {
                    points.push_back(input.GetMousePosition());
                }
            }
        }
        //undo points
        if (input.GetButtonPressed(Input::MouseButton::Right)) {
           if(points.empty()) points.pop_back();
        }

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        /*
         velocity += (force * time.GetDeltaTime());
        */
     
        //RENDER
		renderer.SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        renderer.Clear();

		// Draw random points
        for (int i = 0; i < (int)points.size() - 1; ++i) {
            //renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), 255);
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), 255);
			renderer.DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
        }

        // character
		//renderer.SetColor(1.0f, 1.0f, 1.0f); 
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);
        player.Draw(renderer);

        renderer.Present();
    }

    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}