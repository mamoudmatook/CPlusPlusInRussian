#pragma once

#include <memory>
#include <string>

// Ð˜Ð½Ñ‚ÐµÑ€Ñ„ÐµÐ¹Ñ, Ð¿Ñ€ÐµÐ´ÑÑ‚Ð°Ð²Ð»ÑÑŽÑ‰Ð¸Ð¹ ÐºÐ½Ð¸Ð³Ñƒ
class IBook
{
public:
    virtual ~IBook() = default;

    // Ð’Ð¾Ð·Ð²Ñ€Ð°Ñ‰Ð°ÐµÑ‚ Ð½Ð°Ð·Ð²Ð°Ð½Ð¸Ðµ ÐºÐ½Ð¸Ð³Ð¸
    virtual const std::string &GetName() const = 0;

    // Ð’Ð¾Ð·Ð²Ñ€Ð°Ñ‰Ð°ÐµÑ‚ Ñ‚ÐµÐºÑÑ‚ ÐºÐ½Ð¸Ð³Ð¸ ÐºÐ°Ðº ÑÑ‚Ñ€Ð¾ÐºÑƒ.
    // Ð Ð°Ð·Ð¼ÐµÑ€Ð¾Ð¼ ÐºÐ½Ð¸Ð³Ð¸ ÑÑ‡Ð¸Ñ‚Ð°ÐµÑ‚ÑÑ Ñ€Ð°Ð·Ð¼ÐµÑ€ ÐµÑ‘ Ñ‚ÐµÐºÑÑ‚Ð° Ð² Ð±Ð°Ð¹Ñ‚Ð°Ñ….
    virtual const std::string &GetContent() const = 0;
};

// Ð˜Ð½Ñ‚ÐµÑ€Ñ„ÐµÐ¹Ñ, Ð¿Ð¾Ð·Ð²Ð¾Ð»ÑÑŽÑ‰Ð¸Ð¹ Ñ€Ð°ÑÐ¿Ð°ÐºÐ¾Ð²Ñ‹Ð²Ð°Ñ‚ÑŒ ÐºÐ½Ð¸Ð³Ð¸
class IBooksUnpacker
{
public:
    virtual ~IBooksUnpacker() = default;

    // Ð Ð°ÑÐ¿Ð°ÐºÐ¾Ð²Ñ‹Ð²Ð°ÐµÑ‚ ÐºÐ½Ð¸Ð³Ñƒ Ñ ÑƒÐºÐ°Ð·Ð°Ð½Ð½Ñ‹Ð¼ Ð½Ð°Ð·Ð²Ð°Ð½Ð¸ÐµÐ¼ Ð¸Ð· Ñ…Ñ€Ð°Ð½Ð¸Ð»Ð¸Ñ‰Ð°
    virtual std::unique_ptr<IBook> UnpackBook(const std::string &book_name) = 0;
};

// Ð˜Ð½Ñ‚ÐµÑ€Ñ„ÐµÐ¹Ñ, Ð¿Ñ€ÐµÐ´ÑÑ‚Ð°Ð²Ð»ÑÑŽÑ‰Ð¸Ð¹ ÐºÑÑˆ
class ICache
{
public:
    // ÐÐ°ÑÑ‚Ñ€Ð¾Ð¹ÐºÐ¸ ÐºÑÑˆÐ°
    struct Settings
    {
        // ÐœÐ°ÐºÑÐ¸Ð¼Ð°Ð»ÑŒÐ½Ñ‹Ð¹ Ð´Ð¾Ð¿ÑƒÑÑ‚Ð¸Ð¼Ñ‹Ð¹ Ð¾Ð±ÑŠÑ‘Ð¼ Ð¿Ð°Ð¼ÑÑ‚Ð¸, Ð¿Ð¾Ñ‚Ñ€ÐµÐ±Ð»ÑÐµÐ¼Ñ‹Ð¹ Ð·Ð°ÐºÑÑˆÐ¸Ñ€Ð¾Ð²Ð°Ð½Ð½Ñ‹Ð¼Ð¸
        // Ð¾Ð±ÑŠÐµÐºÑ‚Ð°Ð¼Ð¸, Ð² Ð±Ð°Ð¹Ñ‚Ð°Ñ…
        size_t max_memory = 0;
    };

    using BookPtr = std::shared_ptr<const IBook>;

public:
    virtual ~ICache() = default;

    // Ð’Ð¾Ð·Ð²Ñ€Ð°Ñ‰Ð°ÐµÑ‚ ÐºÐ½Ð¸Ð³Ñƒ Ñ Ð·Ð°Ð´Ð°Ð½Ð½Ñ‹Ð¼ Ð½Ð°Ð·Ð²Ð°Ð½Ð¸ÐµÐ¼. Ð•ÑÐ»Ð¸ ÐµÑ‘ Ð² Ð´Ð°Ð½Ð½Ñ‹Ð¹ Ð¼Ð¾Ð¼ÐµÐ½Ñ‚ Ð½ÐµÑ‚
    // Ð² ÐºÑÑˆÐµ, Ñ‚Ð¾ Ð¿Ñ€ÐµÐ´Ð²Ð°Ñ€Ð¸Ñ‚ÐµÐ»ÑŒÐ½Ð¾ ÑÑ‡Ð¸Ñ‚Ñ‹Ð²Ð°ÐµÑ‚ ÐµÑ‘ Ð¸ Ð´Ð¾Ð±Ð°Ð²Ð»ÑÐµÑ‚ Ð² ÐºÑÑˆ. Ð¡Ð»ÐµÐ´Ð¸Ñ‚ Ð·Ð° Ñ‚ÐµÐ¼,
    // Ñ‡Ñ‚Ð¾Ð±Ñ‹ Ð¾Ð±Ñ‰Ð¸Ð¹ Ð¾Ð±ÑŠÑ‘Ð¼ ÑÑ‡Ð¸Ñ‚Ð°Ð½Ð½Ñ‹Ñ… ÐºÐ½Ð¸Ð³ Ð½Ðµ Ð¿Ñ€ÐµÐ²Ð¾ÑÑ…Ð¾Ð´Ð¸Ð» ÑƒÐºÐ°Ð·Ð°Ð½Ð½Ð¾Ð³Ð¾ Ð² Ð¿Ð°Ñ€Ð°Ð¼ÐµÑ‚Ñ€Ðµ
    // max_memory. ÐŸÑ€Ð¸ Ð½ÐµÐ¾Ð±Ñ…Ð¾Ð´Ð¸Ð¼Ð¾ÑÑ‚Ð¸ ÑƒÐ´Ð°Ð»ÑÐµÑ‚ Ð¸Ð· ÐºÑÑˆÐ° ÐºÐ½Ð¸Ð³Ð¸, Ðº ÐºÐ¾Ñ‚Ð¾Ñ€Ñ‹Ð¼ Ð´Ð¾Ð»ÑŒÑˆÐµ Ð²ÑÐµÐ³Ð¾
    // Ð½Ðµ Ð¾Ð±Ñ€Ð°Ñ‰Ð°Ð»Ð¸ÑÑŒ. Ð•ÑÐ»Ð¸ Ñ€Ð°Ð·Ð¼ÐµÑ€ ÑÐ°Ð¼Ð¾Ð¹ ÐºÐ½Ð¸Ð³Ð¸ ÑƒÐ¶Ðµ Ð±Ð¾Ð»ÑŒÑˆÐµ max_memory, Ñ‚Ð¾ Ð¾ÑÑ‚Ð°Ð²Ð»ÑÐµÑ‚
    // ÐºÑÑˆ Ð¿ÑƒÑÑ‚Ñ‹Ð¼.
    virtual BookPtr GetBook(const std::string &book_name) = 0;
};

// Ð¡Ð¾Ð·Ð´Ð°Ñ‘Ñ‚ Ð¾Ð±ÑŠÐµÐºÑ‚ ÐºÑÑˆÐ° Ð´Ð»Ñ Ð·Ð°Ð´Ð°Ð½Ð½Ð¾Ð³Ð¾ Ñ€Ð°ÑÐ¿Ð°ÐºÐ¾Ð²Ñ‰Ð¸ÐºÐ° Ð¸ Ð·Ð°Ð´Ð°Ð½Ð½Ñ‹Ñ… Ð½Ð°ÑÑ‚Ñ€Ð¾ÐµÐº
std::unique_ptr<ICache> MakeCache(
    std::shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings &settings);