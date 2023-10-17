#ifndef FACTORY_H
#define FACTORY_H


class Factory
{
public:
    Factory();

    bool isDestroyed();
private:
    bool _isDestroyed;
};

#endif // FACTORY_H
