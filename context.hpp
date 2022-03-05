#include <memory>

class Context
{
public:
    Context();

    bool IsDone() const;
    void Done();

    // TODO: maybe adopt PImpl pattern
private:
    std::shared_ptr<bool> is_done;
};
