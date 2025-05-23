#!/bin/bash

echo "=== Clean Architecture Demo ==="
echo "Building the project..."
mkdir -p build
cd build
cmake .. && make

echo ""
echo "=== Running Demo Scenarios ==="

echo ""
echo "1. Creating two users:"
echo "   - Alice (alice@example.com)"
echo "   - Bob (bob@example.com)"

echo ""
echo "2. Listing all users"

echo ""
echo "3. Getting specific user by ID"

echo ""
echo "4. Trying to create user with invalid email"

echo ""
echo "5. Updating a user"

echo ""
echo "6. Deleting a user"

echo ""
echo "=== Demo Input ==="
printf "1\nAlice\nalice@example.com\n\n1\nBob\nbob@example.com\n\n3\n\n2\n1\n\n1\nCharlie\ninvalid-email\n\n4\n1\nAlice Smith\nalice.smith@example.com\n\n5\n2\n\n3\n\n0\n" | ./clean_architecture_demo

echo ""
echo "=== Demo Complete ==="
echo "This demonstrates the Clean Architecture principles:"
echo "- Entities: User business logic"
echo "- Use Cases: UserManager with business rules"
echo "- Interface Adapters: Controller, Presenter, View"
echo "- Frameworks & Drivers: InMemoryUserRepository" 