/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** MessageQueue.hpp
*/

#ifndef MESSAGEQUEUE_HPP_
#define MESSAGEQUEUE_HPP_

#include <string>
#include <mqueue.h>
#include <optional>
#include <ostream>
#include <iostream>
#include <cstring>
#include "ISerializable.hpp"

namespace plazza::utils {
    enum MessagePriority {
        LOW = 0,
        MEDIUM = 1,
        HIGH = 2,
    };

    class MessageQueue {
    public:
        explicit MessageQueue(std::string id, const ssize_t &maxSize) : _id(std::move(id))
        {
            _attributes = {
                    .mq_flags = 0,
                    .mq_maxmsg = maxSize,
                    .mq_msgsize = 1024,
                    .mq_curmsgs = 0,
            };

            _queue = mq_open(_id.c_str(), O_CREAT | O_RDWR | O_NONBLOCK, 0644, &_attributes);

            if (_queue == -1)
                throw std::runtime_error("Cannot create/reach message queue: " + std::string(strerror(errno)));
        }

        ~MessageQueue() noexcept
        {
            mq_close(_queue);
            mq_unlink(_id.c_str());
        }

        [[nodiscard]] bool
        send(const ISerializable &payload, const MessagePriority &priority = MessagePriority::LOW) const
        {
            auto packed = payload.pack();

            if (mq_send(_queue, packed.c_str(), packed.length(), priority) == -1 && errno != EAGAIN)
                throw std::runtime_error("Cannot send message: " + std::string(strerror(errno)));
            return errno != EAGAIN;
        }

        [[nodiscard]] std::optional<std::string> receive() const
        {
            char buffer[_attributes.mq_msgsize + 1];
            memset(buffer, 0, _attributes.mq_msgsize + 1);
            const ssize_t size = mq_receive(_queue, buffer, _attributes.mq_msgsize, nullptr);

            if (size == -1 && errno != EAGAIN)
                throw std::runtime_error("Cannot receive message: " + std::string(strerror(errno)));

            if (size <= 0)
                return std::nullopt;
            return std::string(buffer, size);
        }

        MessageQueue &operator<<(const ISerializable &payload)
        {
            if (!this->send(payload))
                throw std::runtime_error("Cannot send message: " + std::string(strerror(errno)));
            return *this;
        }

        MessageQueue &operator>>(std::optional<std::string> &payload)
        {
            payload = this->receive();
            return *this;
        }

    private:
        const std::string _id;
        mqd_t _queue;
        mq_attr _attributes{};
    };
}

#endif //MESSAGEQUEUE_HPP_
