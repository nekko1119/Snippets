package java8.effective.annotation;

import java.lang.reflect.*;

public class Annotation {
  public static void main(String[] args) throws Exception {
    int tests = 0;
    int passed = 0;
    Class<?> testClass = Class.forName("java8.effective.annotation.TestSample2");
    for (Method m : testClass.getDeclaredMethods()) {
      if (m.isAnnotationPresent(Test.class)) {
        ++tests;
        try {
          m.invoke(null);
        } catch (InvocationTargetException wrappedExc) {
          Throwable exc = wrappedExc.getCause();
          System.out.println(m + " failed: " + exc);
        } catch (Exception exc) {
          System.out.println("INVALID @Test: " + m);
        }
      }
      if (m.isAnnotationPresent(ExceptionTest.class)) {
        ++tests;
        try {
          m.invoke(null);
          System.out.printf("Test %s failed: no exception%n", m);
        } catch (InvocationTargetException wrappedExc) {
          Throwable exc = wrappedExc.getCause();
          Class<? extends Exception>[] excTypes = m.getAnnotation(ExceptionTest.class).value();
          int oldPassed = passed;
          for (Class<? extends Exception> excType : excTypes) {
            if (excType.isInstance(exc)) {
              ++passed;
              break;
            }
          }
          if (passed == oldPassed) {
            System.out.printf("Test %s failed: %s%n", m, exc);
          }
        } catch (Exception exc) {
          System.out.println("INVALID @Test: " + m);
        }
      }
    }
    System.out.printf("Passed: %d, Failed: %d%n", passed, tests - passed);
  }
}