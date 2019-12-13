package org.lab;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.naming.NamingException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author HardRain
 */
@WebServlet(name = "base", urlPatterns = {"/base"})
public class base extends HttpServlet {

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {

            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet base</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h3>ИС-М16 </h1>");
            out.println("<h2>Ryabov Petr </h1>");
            //Тело HTML
            Connection conn = DBconnect.getConn();
            Statement statement = conn.createStatement();
            String sql = "SELECT Name, LastName from PatientCards";
            ResultSet rs = statement.executeQuery(sql);
            int count = 1;
            while (rs.next()) {
                out.println(String.format("Patient #%d: %-15s %s", count++,
                        rs.getString("Name"), rs.getString("LastName")));
            }
            out.println("</body>");
            out.println("</html>");
        } catch (SQLException ex) {
            System.out.println("Statement problem" + ex);
        } catch (NamingException ex) {
            System.out.println("Cannot get connection: " + ex);
        } finally {
            DBconnect.closeConn();
        }
        
    }

// <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
/**
 * Handles the HTTP <code>GET</code> method.
 *
 * @param request servlet request
 * @param response servlet response
 * @throws ServletException if a servlet-specific error occurs
 * @throws IOException if an I/O error occurs
 */
@Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
        public String getServletInfo() {
        return "Short description";
    }// </editor-fold>
}