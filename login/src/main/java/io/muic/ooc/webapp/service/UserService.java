package io.muic.ooc.webapp.service;

import io.muic.ooc.webapp.model.User;
import lombok.Setter;
import org.mindrot.jbcrypt.BCrypt;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;


@Setter
public class UserService {

    private static final String INSERT_USER_SQL = "INSERT INTO tbl_user (username, password, display_name) VALUES (?,?,?);";
    private static final String SELECT_USER_SQL = "SELECT * FROM tbl_user WHERE username = ?;";
    private static final String DELETE_USER_SQL = "DELETE FROM tbl_user WHERE username = ?;";
    private static final String SELECT_ALL_USERS_SQL = "SELECT * FROM tbl_user";


    private static UserService service;
    private DatabaseConnectionService databaseConnectionService;


    private UserService() {
    }

    public static UserService getInstance() {
        if (service == null) {
            service = new UserService();
            service.setDatabaseConnectionService(DatabaseConnectionService.getInstance());
        }
        return service;
    }

    // Create new user
    public void createUser(String username, String password, String displayName) throws UserServiceException {
        try (
                Connection connection = databaseConnectionService.getConnection();
                PreparedStatement ps = connection.prepareStatement(INSERT_USER_SQL);
        ) {
            ps.setString(1, username);
            ps.setString(2, BCrypt.hashpw(password, BCrypt.gensalt())); // Instead of storing raw password, we hash it using BCrypt first and store encrypted version
            ps.setString(3, displayName);
            ps.executeUpdate();
            // manually commit change
            connection.commit();

        } catch (SQLIntegrityConstraintViolationException e) {
            throw new UsernameNotUniqueException(String.format("Username %s has already been taken.", username));
        } catch (SQLException throwables) {
            throw new UserServiceException(throwables.getMessage());
        }
    }

    // Find user by Username
    public User findByUsername(String username) {
        try (
                Connection connection = databaseConnectionService.getConnection();
                PreparedStatement ps = connection.prepareStatement(SELECT_USER_SQL);
        ) {
            ps.setString(1, username);
            ResultSet resultSet = ps.executeQuery();
            resultSet.next();
            return new User(
                    resultSet.getLong("id"),
                    resultSet.getString("username"),
                    resultSet.getString("password"), // Hashed version
                    resultSet.getString("display_name")
            );
        } catch (SQLException throwables) {
            return null;
        }
    }

    // List all user

    /**
     * List all user in the database
     *
     * @return List of all users, never return null
     */
    public List<User> findAll() {
        List<User> users = new ArrayList<>();
        try (
                Connection connection = databaseConnectionService.getConnection();
                PreparedStatement ps = connection.prepareStatement(SELECT_ALL_USERS_SQL);
        ) {
            ResultSet resultSet = ps.executeQuery();
            while (resultSet.next()) {
                User ele = new User(
                        resultSet.getLong("id"),
                        resultSet.getString("username"),
                        resultSet.getString("password"), // Hashed version
                        resultSet.getString("display_name")
                );
                users.add(ele);
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        return users;
    }


    // Delete user

    /**
     * delete user by their Id
     * @param username id
     * @return success or not
     */
    public boolean deleteUserByUsername(String username) {
        try (
                Connection connection = databaseConnectionService.getConnection();
                PreparedStatement ps = connection.prepareStatement(DELETE_USER_SQL);
        ) {
            ps.setString(1, username);
            int deleteCount = ps.executeUpdate();
            connection.commit();
            return deleteCount > 0;
        } catch (SQLException throwables) {
            return false;
        }
    }

    // Update user by user id

    /**
     * User can only change their display name when updating their profile
     *
     * @param id
     * @param displayName
     * @return
     */
    public User uodateUserById(long id, String displayName) {
        throw new UnsupportedOperationException("WIP");
    }

    // Change password

    /**
     * Changing password is its own method, separated from updating profile
     *
     * @param newPassword
     */
    public void changePassword(String newPassword) {
        throw new UnsupportedOperationException("WIP");
    }


    public static void main(String[] args) throws UserServiceException {
        UserService userService = getInstance();

        // Create new User
        userService.createUser("Ren", "12345", "Jove");
        userService.createUser("Amatheyst", "111", "BB");
        userService.createUser("Lasker Uno", "11037", "LEONZ");
//        userService.createUser("admin", "777", "Admin_Jill");

        // Find user by username
//        User user = userService.findByUsername("Etheon");
//        System.out.println(user.getUsername());

        // List all users
//        List<User> all_users = userService.findAll();
//        for (User user : all_users) {
//            System.out.println(user.getUsername());
//        }


    }

}
