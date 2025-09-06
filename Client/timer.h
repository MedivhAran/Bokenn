#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
    Timer() = default;
    ~Timer() = default;

    void restart()
    {
        pass_time = 0;
        shotted = false;
    }

    void set_wait_time(float val)
    {
        wait_time = val;
    }

    void set_one_shot(bool flag)
    {
        one_shot = flag;
    }

    void set_on_timeout(std::function<void()> on_timeout)
    {
        this->on_timeout = on_timeout;
    }

    void pause()
    {
        paused = true;
    }
    void resume()
    {
        paused = false;
	}
    void on_update(float delta)
    {
        if (paused) return;
        pass_time += delta;
        if (pass_time >= wait_time)
        {
			bool can_shot = (!one_shot || (one_shot && !shotted));  //没有触发过并且是一次性的 || 不是一次性的
            shotted = true;
            if (on_timeout && can_shot)
            {
                on_timeout();
            }
            pass_time -= wait_time;
		}
    }

private:
    float pass_time = 0;
    float wait_time = 0;    
    bool shotted = false;   //是否已经触发过（仅用于 one_shot 模式）。
    bool one_shot = false;  //一次性定时器标记
    std::function<void()> on_timeout;   
	bool paused = false;
};

#endif // _TIMER_H_
