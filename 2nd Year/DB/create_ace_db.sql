-- Database: `ace_db`

CREATE DATABASE IF NOT EXISTS ace_db;

USE ace_db;

/*
    Table structure for table `tutor`
    field sizes based on recommended and max lengths
*/

CREATE TABLE IF NOT EXISTS tutor 
(
    tutorID SMALLINT AUTO_INCREMENT NOT NULL,
    firstname VARCHAR(35),
    surname VARCHAR(35) NOT NULL,
    addressLine1 VARCHAR(255) NOT NULL,
    addressLine2 VARCHAR(255),
    town VARCHAR(255) NOT NULL,
    county VARCHAR(35),
    postcode VARCHAR(8) NOT NULL,
    country VARCHAR(35) NOT NULL,
    nextOfKin VARCHAR(70) NOT NULL,
    nextOfKinNumber VARCHAR(15) NOT NULL,
    dateOfBirth date NOT NULL,
    emailAddress VARCHAR(320) NOT NULL UNIQUE,
    officeNum VARCHAR(15),
    extNum VARCHAR(35),
    niNum VARCHAR(9) NOT NULL UNIQUE,
    authorised BOOLEAN NOT NULL DEFAULT FALSE,
    archived BOOLEAN NOT NULL DEFAULT FALSE,

    PRIMARY KEY(tutorID)
);

/*
    Table structure for table `course`
*/
CREATE TABLE IF NOT EXISTS course
(
    courseID SMALLINT AUTO_INCREMENT NOT NULL,
    courseName VARCHAR (35) NOT NULL,
    start DATE,
    end DATE,
    credits TINYINT,
    tutorID SMALLINT,  
    
    PRIMARY KEY(courseID),
    FOREIGN KEY(tutorID) REFERENCES tutor(tutorID) ON UPDATE CASCADE ON DELETE RESTRICT,
    UNIQUE KEY courseTutor(courseName, tutorID)
);

/*
    Table structure for table `student`
*/
CREATE TABLE IF NOT EXISTS student 
(
    studentID SMALLINT AUTO_INCREMENT NOT NULL,
    firstname VARCHAR(35),
    surname VARCHAR(35) NOT NULL,
    addressLine1 VARCHAR(255) NOT NULL,
    addressLine2 VARCHAR(255),
    town VARCHAR(255) NOT NULL,
    county VARCHAR(35),
    postcode VARCHAR(8) NOT NULL,
    country VARCHAR(35) NOT NULL,
    nextOfKin VARCHAR(70) NOT NULL,
    nextOfKinNumber VARCHAR(15) NOT NULL,
    dateOfBirth date NOT NULL,
    emailAddress VARCHAR(320) NOT NULL UNIQUE,
    phone VARCHAR(15),
    feesPaid DECIMAL(7,2),
    authorised BOOLEAN NOT NULL DEFAULT FALSE,

    PRIMARY KEY(studentID)
);

/*
    Table structure for table `studentCourse`
    courses can be ON deleted but student cannot be
*/
CREATE TABLE IF NOT EXISTS studentCourse
(
    studentCourseID SMALLINT AUTO_INCREMENT NOT NULL,
    studentID SMALLINT NOT NULL,
    courseID SMALLINT NOT NULL,
    authorised BOOLEAN NOT NULL DEFAULT FALSE,

    FOREIGN KEY(studentID) REFERENCES student(studentID) ON UPDATE CASCADE ON DELETE RESTRICT,
    FOREIGN KEY(courseID) REFERENCES course(courseID) ON UPDATE CASCADE ON DELETE CASCADE,
    PRIMARY KEY(studentCourseID),
    UNIQUE KEY studentCourse(studentID, courseID)
    
);

/*
    Table structure for table `payment`
    payment cannot be deleted even if course is
*/
CREATE TABLE IF NOT EXISTS payment
(
    paymentID SMALLINT AUTO_INCREMENT NOT NULL,
    amountDue DECIMAL (7,2) NOT NULL,
    datePaid DATE,
    studentCourseID SMALLINT,
    
    PRIMARY KEY(paymentID),
    FOREIGN KEY(studentCourseID) REFERENCES studentCourse(studentCourseID) ON UPDATE CASCADE ON DELETE RESTRICT
);

/*
    Table structure for table `intStudent`
    student cannot be ON deleted
*/
CREATE TABLE IF NOT EXISTS intStudent
(
    studentID SMALLINT NOT NULL,
    passportNumber VARCHAR(9),
    VisaExpirationDate DATE NOT NULL,

    PRIMARY KEY(studentID),
    FOREIGN KEY(studentID) REFERENCES student(studentID) ON UPDATE CASCADE ON DELETE RESTRICT
);

/*
    Table structure for table `resource`
    Type takes on value `Q` or `F` for quiz or file
*/

CREATE TABLE IF NOT EXISTS resource
(
    resourceID SMALLINT AUTO_INCREMENT NOT NULL,
    resourceName VARCHAR(30) NOT NULL,
    tutorID SMALLINT NOT NULL,
    hidden BOOLEAN,
    dateset DATE,
    type ENUM('Q', 'F'),
    deadline DATE,

    PRIMARY KEY(resourceID),
    FOREIGN KEY(tutorID) REFERENCES tutor(tutorID) ON UPDATE CASCADE ON DELETE RESTRICT,
    UNIQUE KEY resourceTutor(resourceName, tutorID)
);

/*
    Table structure for table `courseResource`
    relates resources to courses opposed to tutors and students
*/
CREATE TABLE IF NOT EXISTS courseResource
(
    courseResourceID SMALLINT AUTO_INCREMENT NOT NULL,
    courseID SMALLINT NOT NULL,
    resourceID SMALLINT NOT NULL,

    PRIMARY KEY(courseResourceID),
    FOREIGN KEY(courseID) REFERENCES course(courseID) ON UPDATE CASCADE ON DELETE RESTRICT,
    FOREIGN KEY(resourceID) REFERENCES resource(resourceID) ON UPDATE CASCADE ON DELETE RESTRICT
);

/*
    Table structure for table `quiz`
*/
CREATE TABLE IF NOT EXISTS quiz
(
    courseResourceID SMALLINT NOT NULL,
    studentID SMALLINT NOT NULL,
    percentage DECIMAL(7,2),

    FOREIGN KEY(courseResourceID) REFERENCES courseResource(courseResourceID) ON UPDATE CASCADE ON DELETE RESTRICT,
    FOREIGN KEY(studentID) REFERENCES student(studentID) ON UPDATE CASCADE ON DELETE CASCADE,
    UNIQUE KEY quiz(courseResourceID, studentID)
);

/*
    Table structure for questions
    options defines what type of question this is, if options is empty this is a text question,
    if correct answers is greater than 1 we know its a multiple choice (checkbox),
    otherwise single choice (radio button)
*/

CREATE TABLE IF NOT EXISTS questions
(
    resourceID SMALLINT NOT NULL,
    question TINYTEXT,
    options TINYTEXT,
    correctAnswer VARCHAR(30),
    marks DECIMAL(5,2),

    FOREIGN KEY(resourceID) REFERENCES resource(resourceID) ON UPDATE CASCADE ON DELETE CASCADE
);

/*
    Table structure for table `file`
    resource may need a path field for the path to the resource file
*/
CREATE TABLE IF NOT EXISTS file
(
    resourceID SMALLINT NOT NULL,
    filePath TINYTEXT,

    PRIMARY KEY(resourceID),
    FOREIGN KEY(resourceID) REFERENCES resource(resourceID) ON UPDATE CASCADE ON DELETE CASCADE
);

/*
    users table for login
    type is A,S,T for admin, student, tutor
    requires query to create tutor student etc and then link to user
*/
CREATE TABLE IF NOT EXISTS user
(
    userID SMALLINT NOT NULL,
    emailAddress VARCHAR(320) NOT NULL UNIQUE,
    password TINYTEXT NOT NULL,
    userType ENUM('A', 'S', 'T'),

    PRIMARY KEY(emailAddress)
);