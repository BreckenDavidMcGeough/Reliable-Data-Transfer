
## Overview

This project involves the implementation of three reliable data transport protocols within a given simulator: Alternating-Bit Protocol (ABT), Go-Back-N (GBN), and Selective-Repeat (SR). The objective is to understand and apply the principles of reliable data transmission over an unreliable network.

## Disclaimer

Unfortunately, The project is a part of the CSE4/589 UB organization and is private for academic integrity reasons (so future students of the class can't steal my code), so I was unable to include the commits for the project which displayed the long and extensive development process. For a more in depth and technical view into the functionality of the project, please view the document 'technical_overview.pdf'. For my reports on how I implemented all functionality of project, see the pdf 'pa2-breckenm_pa2.pdf'.

## Objectives

1. Implement ABT, GBN, and SR protocols in the provided simulator.
2. Understand the mechanisms of reliable data transport protocols.
3. Analyze the performance of each protocol under different network conditions.

## Getting Started

### Reading Material

- **Alternating-Bit Protocol (rdt3.0):** Refer to pages 241-245 of the 8th Edition Textbook.
- **Go-Back-N Protocol:** Pages 245-250 of the textbook.
- **Selective-Repeat Protocol:** Pages 250-256 of the textbook.

## Getting Started

You have the option to complete this assignment in either C or C++. To select your language of choice, execute the following command in your terminal. This will merge the chosen language branch into the main branch of your repository.

For C:
```
cd <path_to_your_local_repo>
git fetch --all
git merge origin/c -m "lang option: c" --no-ff && git push origin main
```

For C++:
```
cd <path_to_your_local_repo>
git fetch --all
git merge origin/cpp -m "lang option: cpp" --no-ff && git push origin main
```

## Implementation Details

### Environment

- **Programming Language:** C or C++
- **Compiler:** GCC (GNU Compiler Collection)
- **Development & Testing Environment:** Ensure your code compiles and runs correctly on the assigned CSE host servers.

### Coding Guidelines

- Implement sending and receiving transport-layer code for ABT, GBN, and SR protocols.
- Ensure your code handles message and packet structures as defined in the assignment template.
- You must not involve any disk I/O unless explicitly mentioned in the assignment description.
- Do not modify any routines other than the ones you are supposed to implement.

## Software Interfaces

Your code will interact with simulated network environments. You will implement specific routines such as `A_output`, `A_input`, `A_timerinterrupt`, `A_init`, `B_input`, and `B_init`. Detailed instructions are provided in the PA2 template.

## Testing

Your implementation will be tested against various scenarios to ensure correctness and reliability under different network conditions.

## Resources

To assist you with the assignment, please refer to the following resources:

- **Assignment Handout:** [Link](https://docs.google.com/document/d/19APCj7fT72-ArSbBqp0vaHmpp5uyvX54Mne6zmGYA9g/edit?usp=sharing)
- **Assignment Template:** [Link](https://docs.google.com/document/d/1eXE7z-Z4N458Wvc6fl5wMy1-82PueXOm4dLwZCmOQlA/edit?usp=sharing)
- **Assignment Report Template:** [Link](https://docs.google.com/document/d/1LlQW8mICq8sD6hKqXoOdWb0H2h9FB_wzDZivYMK_u48/edit?usp=sharing)

Please ensure you read through the handout thoroughly before starting the assignment to understand the requirements and deliverables.

## Support

For any doubts or clarifications, please refer to the [Piazza forum](https://piazza.com/class/lr5z5f8jkcz3hb) for our course. Make sure to follow the forum for updates and discussions related to the assignment.

## Submission Guidelines

- Use the `assignment2_package.sh` script to package your submission.
- Ensure your code compiles and runs as expected in the provided environment.
- Submit your assignment through the designated submission portal before the deadline.

Wishing you the best with your assignment!
