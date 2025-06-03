#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class DocumentEditor {
private:
    vector<string> Doc_elements;
    string renderedDoc;
public:
    // Adds text as a plain string
    void addTxt(string txt) {
        Doc_elements.push_back(txt);
    }
    // Adds an image represented by its file path
    void addImg(string imgPath) {
        Doc_elements.push_back(imgPath);
    }
    // Renders the document by checking the type of each element at runtime
    string renderDoc() {
        if(renderedDoc.empty()) {
            string result;
            for(auto element : Doc_elements) {
                if(element.size() > 4 && (element.substr(element.size()-4) == ".jpg" || element.substr(element.size()-4) == ".png")) {
                    result += "[Image: "+ element + "]" + "\n";
                }
                else {
                    result += element + "\n";
                }
            }
            renderedDoc = result;
        }
        return renderedDoc;
    }
    
    void saveToFile() {
        ofstream file("document.txt");
        if(file.is_open()) {
            file<<renderDoc();
            file.close();
            cout<<"Document Saved to document.txt" <<endl;
        }
        else {
            cout<<"Error: Unable to open file for writing."<<endl;
        }
    }
};

int main() {
    DocumentEditor d;
    d.addTxt("Hello World its me the ultimate");
    d.addImg("picture.jpg");
    d.addTxt("This is a document editor.");
    cout<<d.renderDoc()<<endl;
    d.saveToFile();
}
