#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <fstream>


/*class Word
{
    private:
        std::string hidden_string;
        std::string full_hidden_string;
        int letters_number;
        int letters_to_find;
        int life_number;

    public:
        unsigned char letter;
        std::vector<char> found_word{};

        Word(const std::string& word):
            hidden_string(word),
            life_number(5)
            {};

    private:
        void print_found_word()
        {
            std:: cout << "Found word is: " << std::endl;
            for (auto c : found_word) std::cout << c << ' ';
            std:: cout << std::endl;
        }

        void check_letters_number()
        {
            letters_number = hidden_string.size();
            letters_to_find = letters_number;
        }

        void prepare_found_word_vector()
        {
            int new_size = hidden_string.size();
            found_word.resize(new_size);
            std::fill(begin(found_word), end(found_word), '_');
        }

        bool game_over()
        {
            if (life_number == 0)
            {
                std::cout << "Game over, you lost." << std::endl;
                std::cout << "Hidden word was: " << full_hidden_string << std::endl;
                return true;
            }
            else if (letters_to_find == 0)
            {
                std::cout << "Game over, you won." << std::endl;
                return true;
            }
            else
            {
                return false;
            }
        }

        void check_letter()
        {
            auto letter_iterator = std::find(begin(hidden_string), end(hidden_string), letter);

            if (letter_iterator == std::end(hidden_string))
            {
                std::cout << "Letter " << letter << " not found" <<std::endl;
                --life_number;
            }
            else
            {
                char dash = '-';
                while (letter_iterator != std::end(hidden_string))
                {
                    int letter_position = letter_iterator - hidden_string.begin();
                    found_word[letter_position] = letter;
                    hidden_string[letter_position] = dash;
                    --letters_to_find;
                    letter_iterator = std::find(begin(hidden_string), end(hidden_string), letter);
                }
            }
           print_found_word();
        }

        void setup()
        {
            check_letters_number();
            prepare_found_word_vector();
            print_found_word();
            full_hidden_string = hidden_string;
        }

        unsigned char get_letter()
        {
            unsigned char given_letter_= '-';
            while (!(std::isalpha(given_letter_)))
            {
                std::cout << "Give me a letter" << std::endl;
                std::cin >> given_letter_;
                }
            letter = std::tolower(given_letter_);
            return letter;
        }

    public:
        void play_game()
        {
            setup();
            while (!game_over())
            {
                get_letter();
                check_letter();
            }
        }
};*/


struct wordGenerator
{
    std::string text;
    std::string word;
    unsigned char letter_in_text;
    int letter_position;
    const int min_word_size = 6;

    wordGenerator(const std::string& text_):
        text(text_),
        letter_position(0)
        {};

    std::string generate()
    {
        word.clear();
        word.resize(0);

        for (int i = letter_position; i != text.size(); ++i)
        {
            letter_in_text = text[i];

            if((std::isalpha(letter_in_text)))
            {
                letter_in_text = std::tolower(letter_in_text);
                word.push_back(letter_in_text);
            }
            else
            {
                if (word.size()<min_word_size)
                {
                    word.erase();
                    word.resize(0);
                }
                else
                {
                    letter_position = i;
                    //std::cout << "Generated word: " << word << std::endl;
                    //std::cout << "Letter position: " << letter_position << std::endl;
                    return word; //;
                }
            }
        }
        return word; // not necessary, to avoid complier warning "control reaches end of non-void function -wreturn-type"
    }
};

/*bool play_again()
{
    bool ask_again = true;
    unsigned char c;

    while (true)
    {
        std::cout << "Do you want to play again? y/n" << std::endl;
        std::cin >> c;

        if (c == 'y' || c == 'Y')
        {
            return true;
        }
        else if (c == 'n' || c == 'N')
        {
            return false;
        }
        else
        {}
    }
} */

std::string text_generator()
{
    std::string some_text;
    unsigned char c;
    std::ifstream inFile;

    inFile.open("some_text_file.txt");
    if (!inFile)
        {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
        }

    while (inFile >> std::noskipws >> c)
        {
        some_text.push_back(c);
        }

    inFile.close();
    //std::cout << some_text << std::endl;
    return some_text;
}




//////////////////////////////


struct Game
{
    int life_number = 5;
    int letters_to_find;
    std::string full_hidden_string;

    virtual ~Game(){};
    virtual void word_setup() = 0;
    virtual void check_letter() = 0;

   void play_game()
    {
        word_setup();
        while (!game_over())
        {
            check_letter();
        }
    }

    bool game_over()
    {
        if (life_number == 0)
        {
            std::cout << "Game over, you lost." << std::endl;
            std::cout << "Hidden word was: " << full_hidden_string << std::endl;
            return true;
        }
        else if (letters_to_find == 0)
        {
            std::cout << "Game over, you won." << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool play_again()
    {
        bool ask_again = true;
        unsigned char c;

        while (true)
        {
            std::cout << "Do you want to play again? y/n" << std::endl;
            std::cin >> c;

            if (c == 'y' || c == 'Y')
            {
                return true;
            }
            else if (c == 'n' || c == 'N')
            {
                return false;
            }
            else
            {}
        }
    }
};


class Word: public Game
{
    public:
        std::string hidden_string;
        //std::string full_hidden_string;
        int letters_number;
        //int letters_to_find;
        //int life_number;

    public:
        unsigned char letter;
        std::vector<char> found_word{};

        Word(const std::string& word):
            hidden_string(word)
            //life_number(5)
            {};

        void print_found_word()
        {
            std:: cout << "Found word is: " << std::endl;
            for (auto c : found_word) std::cout << c << ' ';
            std:: cout << std::endl;
        }

        void check_letters_number()
        {
            letters_number = hidden_string.size();
            letters_to_find = letters_number;
        }

        void prepare_found_word_vector()
        {
            int new_size = hidden_string.size();
            found_word.resize(new_size);
            std::fill(begin(found_word), end(found_word), '_');
        }

        unsigned char get_letter()
        {
            unsigned char given_letter_= '-';
            while (!(std::isalpha(given_letter_)))
            {
                std::cout << "Give me a letter" << std::endl;
                std::cin >> given_letter_;
                }
            letter = std::tolower(given_letter_);
            return letter;
        }


        void check_letter() override
        {
            get_letter();

            auto letter_iterator = std::find(begin(hidden_string), end(hidden_string), letter);

            if (letter_iterator == std::end(hidden_string))
            {
                std::cout << "Letter " << letter << " not found" <<std::endl;
                --life_number;
            }
            else
            {
                char dash = '-';
                while (letter_iterator != std::end(hidden_string))
                {
                    int letter_position = letter_iterator - hidden_string.begin();
                    found_word[letter_position] = letter;
                    hidden_string[letter_position] = dash;
                    --letters_to_find;
                    letter_iterator = std::find(begin(hidden_string), end(hidden_string), letter);
                }
            }
           print_found_word();
        }

        void word_setup() override
        {
            check_letters_number();
            prepare_found_word_vector();
            print_found_word();
            full_hidden_string = hidden_string;
        }
};


//////////////////////////

int main()
{
    std::string text = text_generator();
    wordGenerator word_generator(text);

    std::string word;
    bool play_again_ = true;

    while (play_again_)
        {
        word = word_generator.generate();

        Word temp_word(word);
        temp_word.play_game();
        play_again_ = temp_word.play_again();
        }

    return 0;
}
