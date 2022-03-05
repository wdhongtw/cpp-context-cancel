#include <memory>

#include "context.hpp"

Context::Context() : is_done(std::make_shared<bool>(false)) {}

bool Context::IsDone() const
{
    return *(this->is_done.get());
}

void Context::Done()
{
    *this->is_done.get() = true;
}
