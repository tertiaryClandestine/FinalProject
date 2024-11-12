class Enemy {
private:
    int hitpoints;
    int attackPower;
    
public:
    Enemy(int _hitpoints) { hitpoints = _hitpoints; }
    virtual void attack() const = 0;
    virtual int getHipoints() const = 0;
};
