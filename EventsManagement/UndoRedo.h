#pragma once
#include <stack>
#include <iostream>
#include <memory>
#include "Event.h"
#include "EventRepository.h"
#include "UserController.h"

// ----- the Command Interface -----
class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

// ----- concrete ICommand commands -----
class AddCommand : public ICommand {
    Event eventAdded;
    EventRepository& rep;
public:
    AddCommand(EventRepository& rep, const Event& e) :rep{ rep }, eventAdded{ e } {}
    void execute() { rep.add_repo(eventAdded); }
    void undo() { rep.remove_repo(eventAdded.getTitle()); }
    void redo() { rep.add_repo(eventAdded); }
};

class DeleteCommand : public ICommand {
    Event eventAdded;
    EventRepository& rep;             
public:
    DeleteCommand(EventRepository& rep, const Event& e) :rep{ rep }, eventAdded{ e } {}
    void execute() { rep.remove_repo(eventAdded.getTitle()); }
    void undo() { rep.add_repo(eventAdded); }
    void redo() { rep.remove_repo(eventAdded.getTitle()); }
};

class UpdateCommand : public ICommand {
    Event oldEvent;
    Event newEvent;
    EventRepository& rep;              
public:
    UpdateCommand(EventRepository& rep, const Event& e1, const Event& e2) :rep{ rep }, oldEvent{ e1 }, newEvent{e2} {}
    void execute() { rep.update_repo(oldEvent, newEvent); }
    void undo() { rep.update_repo(newEvent,oldEvent); }
    void redo() { rep.update_repo(oldEvent, newEvent); }
};

// ----- our CONTROLLER with undo/redo -----
typedef std::stack<std::shared_ptr<ICommand> > commandStack_t;

class CommandManager {
    commandStack_t mUndoStack;
    commandStack_t mRedoStack;

public:
    CommandManager() {}

    void executeCmd(std::shared_ptr<ICommand> command) {
        mRedoStack = commandStack_t(); // clear the redo stack
        command->execute();
        mUndoStack.push(command);
    }

    void undo() {
        if (mUndoStack.size() <= 0) {
            throw std::exception();
        }
        mUndoStack.top()->undo();          // undo most recently executed command
        mRedoStack.push(mUndoStack.top()); // add undone command to undo stack
        mUndoStack.pop();                  // remove top entry from undo stack
    }

    void redo() {
        if (mRedoStack.size() <= 0) {
            throw std::exception();
        }
        mRedoStack.top()->redo();          // redo most recently executed command
        mUndoStack.push(mRedoStack.top()); // add undone command to redo stack
        mRedoStack.pop();                  // remove top entry from redo stack
    }
};
