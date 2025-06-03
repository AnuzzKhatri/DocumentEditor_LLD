#include <iostream>
#include <vector>
#include <string>
#include<fstream>

using namespace std;

// Abstraction for document elements
class DocumentElement{
public:
    virtual string render() = 0;
};

// Concrete implementation for text elements
class TxtElements : public DocumentElement {
private:
    string txt;
public:
    TxtElements(string txt) {
        this->txt = txt;
    }
    string render() override {
        return txt;
    }
};

// Concrete implementation for image elements
class ImgElements : public DocumentElement {
private:
    string ImgPath;
public:
    ImgElements(string ImgPath) {
        this->ImgPath = ImgPath;
    }
    string render() override {
        return "[Image: " + ImgPath + "]";
    }
};

// NewLineElement represents a line break in the document.
class NewLineElement : public DocumentElement {
public:
    string render() override {
        return "\n";
    }
};

// TabSpaceElement represents a tab space in the document.
class TabSpaceElement : public DocumentElement {
public:
    string render() override {
        return "\t";
    }
};

// Document class responsible for holding a collection of elements
class Document {
private:
    vector<DocumentElement*> documentElements;
public:
    void addElements(DocumentElement* element) {
        documentElements.push_back((element));
    }
    // Renders the document by concatenating the render output of all elements.
    string render() {
        string result;
        for (auto element : documentElements) {
            result += element->render();
        }
        return result;
    }
};

// Persistence abstraction
class Persistance {
public:
    virtual void save(string data) = 0;
};

// FileStorage implementation of Persistence
class FileStorage : public Persistance {
public:
    void save(string data) override {
        ofstream outFile("document.txt");
        if (outFile) {
            outFile << data;
            outFile.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// Placeholder DBStorage implementation
class DBStorage : public Persistance {
public:
    void save(string data) override {
        // Save to DB
    }
};

// DocumentEditor class managing client interactions
class DocumentEditor {
private:
    Document* d;
    Persistance* p;
    string renderedDocument;
public:
    DocumentEditor(Document* d, Persistance* p) {
        this->d = d;
        this->p = p;
    }
    void addTxt(string txt) {
        d->addElements(new TxtElements(txt));
    }
    void addImg(string ImgPath) {
        d->addElements(new ImgElements(ImgPath));
    }
    // Adds a new line to the document.
    void addNewLine() {
        d->addElements(new NewLineElement());
    }
    // Adds a tab space to the document.
    void addTabSpace() {
        d->addElements(new TabSpaceElement);
    }
    string renderDocument() {
        if(renderedDocument.empty()) {
            renderedDocument = d->render();
        }
        return renderedDocument;
    }
    void saveDocument() {
        p->save(renderDocument());
    }
};

// Client usage example
int main() {
    Document* d = new Document();
    Persistance* p = new FileStorage();
    
    DocumentEditor* e = new DocumentEditor(d,p);

    // Simulate a client using the editor with common text formatting features.
    e->addTxt("Hello World!");
    e->addNewLine();
    e->addTxt("This is a real-world document editor example.");
    e->addNewLine();
    e->addTabSpace();
    e->addTxt("Indented text after a tab space.");
    e->addNewLine();
    e->addImg("Picture.jpg");

    // Render and display the final document
    cout<<e->renderDocument()<<endl;

    e->saveDocument();
    
    return 0;
}
