#ifndef LOGIC_HPP
#define LOGIC_HPP

namespace Logic
{

class Logic
{
public:
    virtual int run() = 0;
    virtual ~Logic() = default;
};

} // namespace Logic

#endif // LOGIC_HPP
