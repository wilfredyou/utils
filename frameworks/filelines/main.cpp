/**
 * usage example
 */

int main(int argc, char **argv)
{

    FileLines lines("./test.txt");


    std::cout << lines.tostring() << std::endl;


    lines.append("4: 0987654321");


    lines.save();

    lines.refresh();

    std::cout << lines.tostring() << std::endl;

    return 0;
}
