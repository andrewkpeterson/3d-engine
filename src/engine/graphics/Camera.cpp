#include "Camera.h"

Camera::Camera(glm::vec2 screenSize, glm::vec3 eye, float yaw, float pitch, float fov) :
    m_yaw(yaw),
    m_pitch(pitch),
    m_fov(fov),
    m_screenSize(screenSize),
    m_eye(eye),
    m_up(glm::vec3(0, 1, 0)),
    m_forward(glm::vec3(0, 0, 1)),
    m_ui(false),
    m_inverted(false),
    orthographic_ui(false)
{
    glm::mat4x4 mat = glm::perspective(m_fov, m_screenSize.x / m_screenSize.y, nearPlane, farPlane) *
                      glm::lookAt(m_eye, m_eye + getLook(), m_up);
    r_vectors.push_back(glm::vec4(mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0], mat[3][3] - mat[3][0]));
    r_vectors.push_back(glm::vec4(mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1], mat[3][3] - mat[3][1]));
    r_vectors.push_back(glm::vec4(mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2], mat[3][3] - mat[3][2]));
    r_vectors.push_back(glm::vec4(mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat[2][0], mat[3][3] + mat[3][0]));
    r_vectors.push_back(glm::vec4(mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1], mat[3][3] + mat[3][1]));
    r_vectors.push_back(glm::vec4(mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2], mat[3][3] + mat[3][2]));
}

Camera::~Camera()
{
}

const std::vector<glm::vec4> &Camera::getRVectors() {
    return r_vectors;
}

void Camera::recomputeRVectors() {
    glm::mat4x4 mat = glm::perspective(m_fov, m_screenSize.x / m_screenSize.y, nearPlane, farPlane) *
                      glm::lookAt(m_eye, m_eye + getLook(), m_up);
    r_vectors[0] = glm::vec4(mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0], mat[3][3] - mat[3][0]);
    r_vectors[1] = glm::vec4(mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1], mat[3][3] - mat[3][1]);
    r_vectors[2] = glm::vec4(mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2], mat[3][3] - mat[3][2]);
    r_vectors[3] = glm::vec4(mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat[2][0], mat[3][3] + mat[3][0]);
    r_vectors[4] = glm::vec4(mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1], mat[3][3] + mat[3][1]);
    r_vectors[5] = glm::vec4(mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2], mat[3][3] + mat[3][2]);


}

glm::vec2 Camera::getScreenSize()
{
    return m_screenSize;
}

void Camera::setScreenSize(glm::vec2 size)
{
    m_screenSize = size;
    recomputeRVectors();
}

float Camera::getYaw()
{
    return m_yaw;
}

void Camera::setYaw(float yaw)
{
    m_yaw = yaw;
    recomputeRVectors();
}

float Camera::getPitch()
{
    return m_pitch;
}

void Camera::setPitch(float pitch)
{
    m_pitch = pitch;
    recomputeRVectors();
}

float Camera::getFov()
{
    return m_fov;
}

void Camera::setFov(float fov)
{
    m_fov = fov;
    recomputeRVectors();
}

glm::vec3 Camera::getEye()
{
    return m_eye;
}

void Camera::setEye(glm::vec3 eye)
{
    m_eye = eye;
    recomputeRVectors();
}

glm::vec3 Camera::getLook()
{
    glm::vec3 left = glm::normalize(glm::cross(m_up, m_forward));
    glm::vec3 horizontal = glm::cos(m_yaw) * m_forward + glm::sin(m_yaw) * left;
    return glm::cos(m_pitch) * horizontal + glm::sin(m_pitch) * m_up;
}

void Camera::setLook(glm::vec3 look) {
    look = glm::normalize(look);
    glm::vec3 left = glm::normalize(glm::cross(m_up, m_forward));

    float hx = glm::dot(look, m_forward);
    float hy = glm::dot(look, left);
    m_yaw = atan2f(hy, hx);

    float vy = glm::dot(look, m_up);
    m_pitch = (glm::pi<float>() / 2.f) - acosf(vy);
    m_pitch = glm::clamp(static_cast<double>(m_pitch), -M_PI / 2.0 + 0.01, M_PI / 2.0 - 0.01);
    recomputeRVectors();
}

glm::vec3 Camera::getUp() {
    return m_up;
}

void Camera::setUp(glm::vec3 up) {
    m_up = glm::normalize(up);
    recomputeRVectors();
}

void Camera::setOrthographicUI(bool b) {
    orthographic_ui = b;
}

bool Camera::isOrthographicUI() {
    return orthographic_ui;
}

glm::vec3 Camera::getForward() {
    return m_forward;
}

void Camera::setForward(glm::vec3 forward) {
    m_forward = glm::normalize(forward);
    recomputeRVectors();
}

bool Camera::isUI() {
    return m_ui;
}

void Camera::setUI(bool ui) {
    m_ui = ui;
    recomputeRVectors();
}

bool Camera::isInverted() {
    return m_inverted;
}

void Camera::setInverted(bool inverted) {
    m_inverted = inverted;
    recomputeRVectors();
}

void Camera::translate(glm::vec3 vec)
{
    m_eye += vec;
    recomputeRVectors();
}

void Camera::rotate(float yaw, float pitch)
{
    m_yaw += yaw;
    m_pitch += pitch;
    m_pitch = glm::clamp(static_cast<double>(m_pitch), -M_PI / 2.0 + 0.01, M_PI / 2.0 - 0.01);
    recomputeRVectors();
}

glm::mat4 Camera::getView() {
    glm::mat4 view = glm::lookAt(m_eye, m_eye + getLook(), m_up);
    return view;
}

glm::mat4 Camera::getProjection() {
    glm::mat4 proj = glm::perspective(m_fov, m_screenSize.x / m_screenSize.y,
                                      nearPlane, farPlane);
    return proj;
}

glm::mat4 Camera::getUIView() {
    return glm::mat4();
}

glm::mat4 Camera::getUIProjection() {
    glm::mat4 proj;

    // Scale
    if(m_inverted) {
        proj = glm::scale(proj, glm::vec3(2.f / m_screenSize.x, -2.f / m_screenSize.y, 1));
    }
    else {
        proj = glm::scale(proj, glm::vec3(2.f / m_screenSize.x, 2.f / m_screenSize.y, 1));
    }

    // Translate
    proj = glm::translate(proj, glm::vec3(-m_screenSize.x / 2.f, -m_screenSize.y / 2.f, 0));

    return proj;
}
