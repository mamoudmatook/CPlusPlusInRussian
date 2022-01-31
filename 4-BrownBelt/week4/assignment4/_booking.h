namespace RAII
{
    template <typename P>
    class Booking
    {
    public:
        Booking(P *p, int count) : provider_(p), counter_(count) {}
        Booking(const Booking &other) = delete;
        Booking(Booking &&other)
        {
            if (this != &other)
            {
                provider_ = other.provider_;
                other.provider_ = nullptr;
            }
        }
        Booking<P> &operator=(Booking &other) = delete;
        Booking<P> &operator=(Booking &&other)
        {
            if (this != &other)
            {
                delete provider_;
                provider_ = other.provider_;
                other.provider_ = nullptr;
            }
            return *this;
        }
        ~Booking()
        {
            if (provider_ != nullptr)
            {
                provider_->CancelOrComplete(*this);
            }
        }

    private:
        P *provider_;
        int counter_;
    };
};
