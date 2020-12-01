#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkTIFFReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkImageResize.h>

int main(int argc, char* argv[])
{
    const std::string path = "/Users/aramirez/Documents/SciViz/Proyecto/COL Forest Change/";
    const std::string originalFileName = "ForestData.tif";

    for (int i = 1; i <= 19; ++i) {
        //Read the image
        vtkSmartPointer<vtkTIFFReader> reader =
                vtkSmartPointer<vtkTIFFReader>::New();
        reader->SetFileName ((path + originalFileName).c_str());
        reader->Update();

        vtkSmartPointer<vtkImageData> image = reader->GetOutput();
        int* dims = image->GetDimensions();
        for (int z=0; z<dims[2]; z++)
        {
            for (int y=0; y<dims[1]; y++)
            {
                for (int x=0; x<dims[0]; x++)
                {
                    // zero is the component, add another loop if you have more
                    // than one component
                    double v = image->GetScalarComponentAsDouble(x,y,z,0);

                    if(v <= i){
                        v = 0;
                    }
                    else
                    {
                        v = 255;
                    }
                    image->SetScalarComponentFromDouble(x, y, z, 0, v);
                }
            }
        }
        vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
        resize->SetInputData(image);
        resize->SetOutputDimensions(1080, 1080, 1);
        resize->Update();

        std::string fileName = "b_" + std::to_string(2000 + i) + ".1080.png";
        vtkSmartPointer<vtkPNGWriter> jWriter = vtkSmartPointer<vtkPNGWriter>::New();
        jWriter->SetFileName((path + fileName).c_str());
        jWriter->SetInputData(resize->GetOutput());
        jWriter->Write();
    }




/*
  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(reader->GetOutputPort());
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();

  renderWindowInteractor->Start();*/

  return EXIT_SUCCESS;
}
