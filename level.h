#ifndef LEVEL_H
#define LEVEL_H


class level
{
public:
    level();
    virtual void create_board() = 0;
    virtual void add_board_images() = 0;
    virtual void create_player() = 0;
    virtual void create_enemies() = 0;
    virtual void create_bullets() = 0;
    virtual void create_pellets() = 0;
    virtual void create_healthbar() = 0;
    virtual void remove_bullets() = 0;
    virtual void open_gate() = 0;
    virtual void close_gate() = 0;
    virtual void updateCounters() = 0;
    virtual void restart_game() = 0;
    virtual void updateModeTxt() = 0;
    virtual void remove_heart() = 0;
    virtual void player_hit() = 0;
};

#endif // LEVEL_H
