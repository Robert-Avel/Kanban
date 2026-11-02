#include <string>

namespace kb
{
    class Task {
        protected:
            std::string title;
            std::string description;
            bool marked;

        public:
            Task() = delete;
            Task(std::string title_, std::string description_): title(title_), description(description_), marked(false) {}

            void setTitle(std::string title_) {this->title = title_;}
            const std::string& getTitle() const {return this->title;}

            void setDescription(std::string description_) {this->description = description_;}
            const std::string& getDescription() const {return this->description;}

            bool Markable() const {return true;}

            bool Mark(bool force) {marked = true; return true;}
            void unMark() {marked = false;}
            bool switchMark(bool force) {marked = !marked; return marked;}

            bool getMark() const {return marked;}
    };
};
