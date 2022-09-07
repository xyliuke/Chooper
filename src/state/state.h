//
// Created by ke liu on 27/01/2018.
// Copyright (c) 2018 ke liu. All rights reserved.
//

#ifndef ANET_STATE_MACHINE_H
#define ANET_STATE_MACHINE_H

#include <functional>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>

namespace plan9 {
    class StateMachine;


    class State {
    public:
        State();
        virtual void OnEntry(std::string &event, StateMachine* fsm) {}
        virtual void OnExit(std::string &event, StateMachine* fsm) {}
        virtual const std::type_info& GetType();
        virtual void Exec() {}
    };

    class TransitionRow {
    public:

        template <typename B, typename E>
        static std::shared_ptr<TransitionRow> Get(StateMachine* fsm, std::string event, std::function<bool(StateMachine*)> action) {
            std::shared_ptr<TransitionRow> ret = std::make_shared<TransitionRow>(event, action);
            ret->SetState<B, E>(fsm);
            return ret;
        }

        /**
         * 定义一个迁移的事件
         * @param event 迁移的事件
         * @param action 迁移的动作，返回true表示同意迁移，返回false表示不同意迁移
         */
        TransitionRow(std::string event, std::function<bool(StateMachine*)> action)
                : event_(std::move(event)), action_(std::move(action)) {
        }
        /**
         * 设置移动的起始和终止状态
         * @tparam B 一条迁移的起始状态类型
         * @tparam E 一条迁移的终止起始状态
         */
        template <typename B, typename E>
        void SetState(StateMachine* fsm) {
            b_hash_code = typeid(B).hash_code();
            e_hash_code = typeid(E).hash_code();
            std::shared_ptr<std::map<size_t, std::shared_ptr<State>>> m;
            if (map_.find(fsm) != map_.end()) {
                m = map_[fsm];
            } else {
                m = std::make_shared<std::map<size_t, std::shared_ptr<State>>>();
                map_[fsm] = m;
            }
            if (m->find(b_hash_code) == m->end()) {
                std::shared_ptr<State> obj = std::make_shared<B>();
                (*m)[b_hash_code] = obj;
            }
            if (m->find(e_hash_code) == m->end()) {
                std::shared_ptr<State> obj = std::make_shared<E>();
                (*m)[e_hash_code] = obj;
            }

            set_trace(typeid(B), typeid(E));

        }

        bool IsMatch(std::string event, size_t begin) {
            return event_ == event && begin == b_hash_code;
        }

        bool ExecAction(StateMachine* fsm) {
            if (action_) {
                return action_(fsm);
            }
            return true;
        }

        size_t GetEnd() {
            return e_hash_code;
        }

        static std::shared_ptr<State> Get(StateMachine* fsm, size_t hash_code) {
            std::shared_ptr<State> ret;
            if (map_.find(fsm) != map_.end()) {
                auto m = map_[fsm];
                if (m->find(hash_code) != m->end()) {
                    return (*m)[hash_code];
                }
            }
            return ret;
        }
        static void Remove(StateMachine* fsm) {
            map_.erase(fsm);
        }

        std::string ToString() {
            return trace;
        }

    private:
        size_t b_hash_code = {0};
        size_t e_hash_code = {0};
        const std::string event_;
        const std::function<bool(StateMachine*)> action_;
        static std::map<StateMachine*, std::shared_ptr<std::map<size_t, std::shared_ptr<State>>>> map_;
        std::string trace;
        void set_trace(const std::type_info& t1, const std::type_info& t2);
    };

    class StateMachine {
    public:
        StateMachine();
        ~StateMachine();

        /**
         * 设置初始状态
         * @tparam T 状态的类型
         */
        template <typename T>
        void SetInitState() {
            current = typeid(T).hash_code();
        }
        /**
         * 状态机的开始
         */
        void Start();
        /**
         * 触发某个事件
         * @param event 事件名
         */
        void ProcessEvent(std::string event);
        /**
         * 找不到对应的迁移状态后触发的函数
         * @param begin 触发前的状态
         * @param event 事件
         */
        virtual void NoTransition(std::shared_ptr<State> begin, std::string event);

        template <typename B, typename E>
        void AddRow(std::string event, std::function<bool(StateMachine*)> action) {
            rows->push_back(TransitionRow::Get<B, E>(this, event, action));
        };
        /**
         * 是否记录迁移动作，默认为false
         * @param trace true表示记录
         */
        void SetTrace(bool trace, std::function<void(std::string)> callback);

        /**
         * 判断当前是否指定状态
         * @tparam T 状态类
         * @return true表示当前状态相同
         */
        template <typename T>
        bool IsCurrentState() {
            const std::type_info& t = typeid(T);
            return t.hash_code() == current;
        }

        std::string GetTrace();
    private:
        void record(std::shared_ptr<TransitionRow> row);
        std::shared_ptr<std::vector<std::shared_ptr<TransitionRow>>> rows;
        size_t current;
        std::shared_ptr<std::vector<std::shared_ptr<TransitionRow>>> trace;
        bool is_trace;
        std::function<void(std::string)> trace_callback;
    };

#define STATE_MACHINE_ADD_ROW(state_machine_ptr, begin, event, end, action) (state_machine_ptr)->AddRow<begin, end>(event, action)
}


#endif //ANET_STATE_MACHINE_H