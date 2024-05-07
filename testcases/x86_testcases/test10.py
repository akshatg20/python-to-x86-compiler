class Employee:
    def __init__(self, name : str, emp_id : str, department : str) -> None:
        self.name : str = name
        self.emp_id : str = emp_id
        self.department : str = department
        return

    def display_info(self) -> None:
        print("Name: ", self.name)
        print("Employee ID: ", self.emp_id)
        print("Department: ", self.department)
        return

class Manager(Employee):
    def __init__(self, name : str, emp_id : str, department : str) -> None:
        Employee.__init__(self, name, emp_id, department)
        self.technician1 : Employee = Employee("", "", "")
        self.technician2 : Employee = Employee("", "", "")
        self.under : int = 0
        return

    def add_technician(self, technician : Employee) -> None:
        if self.under == 0:
            self.technician1 = technician
            self.under = self.under + 1
        elif self.under == 1:
            self.technician2 = technician
            self.under = self.under + 1
        else:
            print("No more space for any technician under manager ", self.name)
        return

    def display_team_info(self) -> None:
        Employee.display_info(self)
        print("Technicians under this manager: ")
        technician1 : Employee = (self.technician1)
        technician1.display_info()
        print()
        technician2 : Employee = (self.technician2)
        technician2.display_info()
        print()
        return

class Technician(Employee):
    def __init__(self, name : str, emp_id : str, department : str, manager : Employee) -> None:
        Employee.__init__(self, name, emp_id, department)
        self.manager : Employee = manager
        return

    def display_info(self) -> None:
        Employee.display_info(self)
        manager : Employee = self.manager
        manager_name : str = manager.name
        print("Manager: ", manager_name)
        return

# Example usage:
if __name__ == "__main__":
    # Creating employees
    manager1 = Manager("John Doe", "M001", "Management")
    technician1 = Technician("Alice Smith", "T001", "IT", manager1)
    technician2 = Technician("Bob Johnson", "T002", "IT", manager1)

    manager2 = Manager("Jane Smith", "M002", "HR")
    technician3 = Technician("Carol Williams", "T003", "HR", manager2)

    # Adding technicians to managers
    manager1.add_technician(technician1)
    manager1.add_technician(technician2)
    manager2.add_technician(technician3)

    # Displaying information
    manager1.display_team_info()
    manager2.display_team_info()
