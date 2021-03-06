﻿/*********************************************************************************
*  Copyright (c) 2017-2018 DeepBrainChain core team
*  Distributed under the MIT software license, see the accompanying
*  file COPYING or http://www.opensource.org/licenses/mit-license.php
* file name        :   topic_manager.h
* description    :   topic manager 
* date                  :   2018.01.20
* author            :   Bruce Feng
**********************************************************************************/
#ifndef _TOPIC_MANAGER_H_
#define _TOPIC_MANAGER_H_

#include <string>
#include "module.h"
#include "rw_lock.h"
#include "function_traits.h"

using namespace std;

extern const std::string topic_manager_name;

namespace matrix
{
    namespace core
    {
        class topic_manager : public module
        {
        public:

            typedef std::multimap<std::string, boost::any>::iterator iterator_type;

            virtual ~topic_manager() { write_lock_guard<rw_lock> lock_guard(m_lock); m_topic_registry.clear(); }

            virtual std::string module_name() const { return topic_manager_name; }

        public:

            //subscribe topic from bus
            template<typename function_type>
            void subscribe(const std::string &topic, function_type &&f)
            {
                auto func = to_function(std::forward<function_type>(f));
                add(topic, std::move(func));
            }

            //publish topic to bus with args function
            template<typename ret_type, typename... args_type>
            void publish(const std::string &topic, args_type&&... args)
            {
                using function_type = std::function<ret_type (args_type...)>;
                std::string msg_type = topic + typeid(function_type).name();

                if (topic != "time_tick_notification")
                {
                    LOG_DEBUG << "topic manager publish: "<<topic;
                }

                read_lock_guard<rw_lock> lock_guard(m_lock);
                auto range = m_topic_registry.equal_range(msg_type);
                if (range.first == range.second)
                {
                    LOG_ERROR << "1 topic manager could not find topic invoke function: " << topic;
                    return;
                }

                for (iterator_type it = range.first; it != range.second; it++)
                {
                    auto f = boost::any_cast<function_type>(it->second);
                    f(std::forward<args_type>(args)...);
                }
            }

            //publish topic to bus with no args function
            template<typename function_type>
            void publish(const std::string &topic)
            {
//                using std_function_type = std::function<function_type()>;
                std::string msg_type = topic + typeid(function_type).name();

                read_lock_guard<rw_lock> lock_guard(m_lock);
                auto range = m_topic_registry.equal_range(msg_type);
                if (range.first == m_topic_registry.end())
                {
                    LOG_ERROR << "2 topic manager could not find topic invoke function: " << topic;
                    return;
                }

                for (iterator_type it = range.first; it != range.second; it++)
                {
                    auto f = boost::any_cast<function_type>(it->second);
                    f();
                }
            }

            //unsubscribe
            template<typename ret_type, typename...args_type>
            void unsubscribe(const std::string &topic)
            {
                using function_type = std::function<ret_type(args_type...)>;
                std::string msg_type = topic + typeid(function_type).name();

                write_lock_guard<rw_lock> lock_guard(m_lock);
                int count = m_topic_registry.count(msg_type);
                if (0 == count)
                {
                    return;
                }
                auto range = m_topic_registry.equal_range(msg_type);
                m_topic_registry.erase(range.first, range.second);
            }

        protected:

            template<typename function_type>
            void add(const std::string &topic, function_type &&func)
            {
                std::string msg_type = topic + typeid(function_type).name();

                write_lock_guard<rw_lock> lock_guard(m_lock);
                m_topic_registry.emplace(std::move(msg_type), std::forward<function_type>(func));
            }

        protected:

            rw_lock m_lock;

            std::multimap<std::string, boost::any> m_topic_registry;

        };

    }

}

#endif 
