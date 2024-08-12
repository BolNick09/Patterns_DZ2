#include <iostream>
#include <unordered_map>


//Паттерн Прототип
class Biome 
{
public:
    virtual Biome* clone() = 0;
    virtual void print() = 0;
};

class Forest : public Biome 
{
private:
    std::string treeType;
    std::string wildlife;

public:
    Forest(const std::string& treeType, const std::string& wildlife)
        : treeType(treeType), wildlife(wildlife) {}

    Biome* clone() override 
    {
        return new Forest(*this);
    }

    void print() override 
    {
        std::cout << "Forest with " << treeType << " trees and " << wildlife << " wildlife." << std::endl;
    }
};

class Desert : public Biome 
{
private:
    std::string sandType;
    std::string climate;
public:
    Desert(const std::string& sandType, const std::string& climate)
        : sandType(sandType), climate(climate) {}

    Biome* clone() override     
    {
        return new Desert(*this);
    }

    void print() override 
    {
        std::cout << "Desert with " << sandType << " sand and " << climate << " climate." << std::endl;
    }
};

class Ocean : public Biome 
{
public:
    Ocean(const std::string& waterType, const std::string& marineLife)
        : waterType(waterType), marineLife(marineLife) {}

    Biome* clone() override 
    {
        return new Ocean(*this);
    }

    void print() override 
    {
        std::cout << "Ocean with " << waterType << " water and " << marineLife << " marine life." << std::endl;
    }

private:
    std::string waterType;
    std::string marineLife;
};

class BiomeFactory 
{
    std::unordered_map<std::string, Biome*> prototypes;
public:
    void registerBiome(const std::string& name, Biome* prototype)
    {
        prototypes[name] = prototype;
    }
    Biome* createBiome(const std::string& name) 
    {
        return prototypes[name]->clone();
    }
    ~BiomeFactory() 
    {
        for (auto& pair : prototypes)         
            delete pair.second;        
    }
};
//------------------------------------------------------------------------------
//Паттерн Билдер
class Computer 
{
private:
    std::string processor;
    std::string ram;
    std::string storage;

public:
    void setProcessor(const std::string& processor) 
    {
        this->processor = processor;
    }

    void setRAM(const std::string& ram) 
    {
        this->ram = ram;
    }

    void setStorage(const std::string& storage) 
    {
        this->storage = storage;
    }

    void show() 
    {
        std::cout << "Computer with " << processor << " processor, " << ram << " RAM, and " << storage << " storage." << std::endl;
    }
};
class ComputerBuilder 
{
public:
    virtual void buildProcessor() = 0;
    virtual void buildRAM() = 0;
    virtual void buildStorage() = 0;
    virtual Computer* getComputer() = 0;
};
class GamingComputerBuilder : public ComputerBuilder 
{
private:
    Computer* computer;

public:
    GamingComputerBuilder() 
    {
        computer = new Computer();
    }

    void buildProcessor() override 
    {
        computer->setProcessor("Intel i9");
    }

    void buildRAM() override 
    {
        computer->setRAM("32GB");
    }

    void buildStorage() override 
    {
        computer->setStorage("1TB SSD");
    }

    Computer* getComputer() override 
    {
        return computer;
    }
};

class OfficeComputerBuilder : public ComputerBuilder 
{
private:
    Computer* computer;
public:
    OfficeComputerBuilder() 
    {
        computer = new Computer();
    }

    void buildProcessor() override 
    {
        computer->setProcessor("Intel i5");
    }

    void buildRAM() override 
    {
        computer->setRAM("16GB");
    }

    void buildStorage() override 
    {
        computer->setStorage("512GB SSD");
    }

    Computer* getComputer() override 
    {
        return computer;
    }
};
class Director 
{
    ComputerBuilder& builder;
public:
    Director(ComputerBuilder& b) : builder(b) {}
    void construct() 
    {
        builder.buildProcessor();
        builder.buildRAM();
        builder.buildStorage();
    }
};
//------------------------------------------------------------------------------
//Паттерн Factory
class Report 
{
public:
    virtual void generate() = 0;
};

class ReportCreator 
{
public:
    virtual Report* createReport() = 0;
    void generateReport() 
    {
        Report* report = createReport();
        report->generate();
        delete report;
    }
};

class PDFReport : public Report 
{
public:
    void generate() override 
    {
        std::cout << "Generating a PDF report." << std::endl;
    }
};

class HTMLReport : public Report
{
public:
    void generate() override 
    {
        std::cout << "Generating an HTML report." << std::endl;
    }
};

class PDFReportCreator : public ReportCreator 
{
public:
    Report* createReport() override 
    {
        return new PDFReport();
    }
};

class HTMLReportCreator : public ReportCreator 
{
public:
    Report* createReport() override 
    {
        return new HTMLReport();
    }
};
//------------------------------------------------------------------------------
//Паттерн Abstract factory
class VideoPlayer 
{
public:
    virtual void play() = 0;
};

class AudioPlayer 
{
public:
    virtual void play() = 0;
};

class MultimediaFactory 
{
public:
    virtual VideoPlayer* createVideoPlayer() = 0;
    virtual AudioPlayer* createAudioPlayer() = 0;
};

class WindowsVideoPlayer : public VideoPlayer 
{
public:
    void play() override 
    {
        std::cout << "Playing video on Windows." << std::endl;
    }
};

class MacVideoPlayer : public VideoPlayer 
{
public:
    void play() override 
    {
        std::cout << "Playing video on Mac." << std::endl;
    }
};

class WindowsAudioPlayer : public AudioPlayer 
{
public:
    void play() override 
    {
        std::cout << "Playing audio on Windows." << std::endl;
    }
};

class MacAudioPlayer : public AudioPlayer 
{
public:
    void play() override 
    {
        std::cout << "Playing audio on Mac." << std::endl;
    }
};

class WindowsMultimediaFactory : public MultimediaFactory 
{
public:
    VideoPlayer* createVideoPlayer() override 
    {
        return new WindowsVideoPlayer();
    }

    AudioPlayer* createAudioPlayer() override 
    {
        return new WindowsAudioPlayer();
    }
};

class MacMultimediaFactory : public MultimediaFactory 
{
public:
    VideoPlayer* createVideoPlayer() override 
    {
        return new MacVideoPlayer();
    }

    AudioPlayer* createAudioPlayer() override 
    {
        return new MacAudioPlayer();
    }
};


//------------------------------------------------------------------------------
int main() 
{
    std::cout << "Prototype pattern" << std::endl;
    BiomeFactory biomeFactory;

    biomeFactory.registerBiome("Forest", new Forest("Pine", "Deer"));
    biomeFactory.registerBiome("Desert", new Desert("Golden", "Hot"));
    biomeFactory.registerBiome("Ocean", new Ocean("Salt", "Fish"));

    Biome* forestClone = biomeFactory.createBiome("Forest");
    forestClone->print(); // Вывод: Forest with Pine trees and Deer wildlife.

    Biome* desertClone = biomeFactory.createBiome("Desert");
    desertClone->print(); // Вывод: Desert with Golden sand and Hot climate.

    Biome* oceanClone = biomeFactory.createBiome("Ocean");
    oceanClone->print(); // Вывод: Ocean with Salt water and Fish marine life.

    delete forestClone;
    delete desertClone;
    delete oceanClone;

    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "Builder pattern" << std::endl;
    GamingComputerBuilder gamingBuilder;
    Director director(gamingBuilder);
    director.construct();
    Computer* gamingComputer = gamingBuilder.getComputer();
    gamingComputer->show(); // Вывод: Computer with Intel i9 processor, 32GB RAM, and 1TB SSD storage.

    OfficeComputerBuilder officeBuilder;
    Director officeDirector(officeBuilder);
    officeDirector.construct();
    Computer* officeComputer = officeBuilder.getComputer();
    officeComputer->show(); // Вывод: Computer with Intel i5 processor, 16GB RAM, and 512GB SSD storage.
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "Factory pattern" << std::endl;
    ReportCreator* pdfCreator = new PDFReportCreator();
    pdfCreator->generateReport(); // Вывод: Generating a PDF report.
    delete pdfCreator;

    ReportCreator* htmlCreator = new HTMLReportCreator();
    htmlCreator->generateReport(); // Вывод: Generating an HTML report.
    delete htmlCreator;
    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "Abstract factory pattern" << std::endl;
    MultimediaFactory* factory;

    // Создание мультимедийных элементов для Windows
    factory = new WindowsMultimediaFactory();
    VideoPlayer* windowsVideoPlayer = factory->createVideoPlayer();
    AudioPlayer* windowsAudioPlayer = factory->createAudioPlayer();
    windowsVideoPlayer->play(); // Вывод: Playing video on Windows.
    windowsAudioPlayer->play(); // Вывод: Playing audio on Windows.
    delete windowsVideoPlayer;
    delete windowsAudioPlayer;
    delete factory;

    // Создание мультимедийных элементов для Mac
    factory = new MacMultimediaFactory();
    VideoPlayer* macVideoPlayer = factory->createVideoPlayer();
    AudioPlayer* macAudioPlayer = factory->createAudioPlayer();
    macVideoPlayer->play(); // Вывод: Playing video on Mac.
    macAudioPlayer->play(); // Вывод: Playing audio on Mac.
    delete macVideoPlayer;
    delete macAudioPlayer;
    delete factory;






    return 0;
}


