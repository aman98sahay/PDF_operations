
#include <iostream>
#include <podofo/podofo.h>


using namespace std;
using namespace PoDoFo;

int main(int argc, char const *argv[])
{
    if (argc != 3) {

        printf("This program must be called with the locations of 2 pdf files passed as well."); 
        return 1;
    }

    PdfMemDocument document1;
    PdfMemDocument document2;

    document1.Load(argv[1]);
    document2.Load(argv[2]);

    PdfPainter painter1;

    auto& page1_1 = document1.GetPages().GetPageAt(0);

    PdfFont* font = document1.GetFonts().SearchFont("Arial");

    painter1.TextState.SetFont(*font, 20);
    
    painter1.SetCanvas(page1_1);
    
    

    
    painter1.DrawText("ABCDEFGHIKLMNOPQRSTVXYZ", 56.69, page1_1.GetRect().Height - 56.69);

    painter1.FinishDrawing();

    document1.Save("./output1.pdf");
    
    return 0;
}
