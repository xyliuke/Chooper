//
// Created by ke liu on 27/01/2018.
// Copyright (c) 2018 ke liu. All rights reserved.
//

#include <sstream>
#include <thread>
#include "state.h"

namespace plan9
{
    std::map<state_machine*, std::shared_ptr<std::map<size_t, std::shared_ptr<state>>>> TransitionRow::map_;

    State::State() {
    }

    const std::type_info& State::GetType() {
        return typeid(this);
    }

    void TransitionRow::set_trace(const std::type_info &t1, const std::type_info &t2) {
        std::stringstream ss;
        ss << t1.name();
        ss <<  " -> ";
        ss << event_;
        ss << " -> ";
        ss <<  t2.name();
        trace = ss.str();
    }

    StateMachine::StateMachine() : current(0), rows(std::make_shared<std::vector<std::shared_ptr<TransitionRow>>>()),
                                   trace(std::make_shared<std::vector<std::shared_ptr<TransitionRow>>>()),
                                   is_trace(false) {

    }

    StateMachine::~StateMachine() {
        TransitionRow::Remove(this);
    }

    void StateMachine::Start() {
        if (current > 0) {
            auto c = TransitionRow::Get(this, current);
            if (c) {
                c->OnEntry("no_event", this);
            }
        }
    }

    void StateMachine::ProcessEvent(std::string event) {
        bool exist = false;
        for (int i = 0; i < rows->size(); ++i) {
            auto row = (*rows)[i];
            if (row->IsMatch(event, current)) {
                exist = true;
                if (row->ExecAction(this)) {
                    record(row);
                    auto c_state = TransitionRow::Get(this, current);
                    if (c_state) {
                        c_state->OnExit(event, this);
                    }

                    current = row->GetEnd();
                    auto n_state = TransitionRow::Get(this, current);
                    if (n_state) {
                        n_state->OnEntry(event, this);
                    }
                    break;
                }
            }
        }
        if (!exist) {
            NoTransition(TransitionRow::Get(this, current), event);
            if (is_trace && trace_callback) {
                std::stringstream ss;
                ss << "thread : ";
                ss << std::this_thread::get_id();
                ss << "\t";
                ss << event;
                ss << "\t";
                ss << "no transition";
                trace_callback(ss.str());
            }
        }
    }

    void StateMachine::no_transition(std::shared_ptr<state> begin, std::string event) {
    }

    void StateMachine::record(std::shared_ptr<TransitionRow> row) {
        if (is_trace) {
            trace->push_back(row);
            if (trace_callback) {
                std::stringstream ss;
                ss << "thread : ";
                ss << std::this_thread::get_id();
                ss << "\t";
                ss << row->to_string();
                trace_callback(ss.str());
            }
        }
    }
    void StateMachine::set_trace(bool trace, std::function<void(std::string)> callback) {
        is_trace = trace;
        trace_callback = callback;
    }
    std::string StateMachine::get_trace() {
        std::stringstream ss;
        auto it = trace->begin();
        while (it != trace->end()) {
            ss << (*it)->to_string();
            ss << "\n";
            it ++;
        }
        return ss.str();
    }
}